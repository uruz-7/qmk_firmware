# QMK Firmware Upgrade Log: HHKB RN42 Mod
**Date:** February 5, 2026
**Target Device:** HHKB Professional 2 with Custom RN42 Bluetooth Module
**Microcontroller:** ATMega32U4
**Starting Version:** 0.7.172
**Final Version:** 0.31.8

---

## Executive Summary
This document records the incremental upgrade path taken to bring the HHKB RN42 firmware from legacy versions (2016-era) to modern QMK (2025/2026). The primary challenge was preserving the custom Bluetooth logic (`rn42`, `battery`, `suart`, `serial_uart`) which is not natively supported by QMK's modern data-driven build system (`info.json`).

**Key Strategy:**
1.  **Stash & Carry:** Creating a persistent git stash of the custom RN42 files (`keyboards/hhkb/rn42/*`) and the custom `keymap.c` and `rules.mk`.
2.  **Force Legacy Mode:** Deliberately deleting `keyboards/hhkb/ansi/info.json` in newer versions to force QMK to use our manual `rules.mk`, which contains the logic to compile the Bluetooth drivers.
3.  **Python Patching:** Manually patching QMK's python build scripts to support Python 3.14 (specifically `ast.Num` vs `ast.Constant`) until version 0.31.0 where it was fixed upstream.

---

## Detailed Version History

### Phase 1: The Foundation (Legacy)

#### **v0.7.172 → v0.17.9**
*   **Status:** Successful
*   **Context:** These versions represent the "Classic Era" of QMK, relying heavily on recursive Makefiles before the data-driven refactor.
*   **Key Actions:**
    *   **Custom Driver Integration:** Manually established the RN42 Bluetooth stack sources. Copied `suart.S` (Software UART assembly), `serial_uart.c`, and `rn42.c` into the custom directory `keyboards/hhkb/rn42/`.
    *   **Build Configuration:** Created the specific `rules.mk` to include these drivers via `VPATH` and `SRC` append operations. This was critical because the default QMK build system does not know about these custom driver files.
    *   **Target Verification:** Confirmed `MCU = atmega32u4` settings were correctly picked up by the build environment.

#### **v0.21.7**
*   **Status:** Successful 
*   **Firmware Size:** ~23KB
*   **Key Actions:**
    *   **Workflow Verification:** Established the `git stash` (include untracked) -> `checkout` -> `git stash pop` workflow. This proved essential to carry the untracked `rn42` folder and custom keymaps across version control checkouts without data loss.
    *   **Configuration Check:** Verified that `HHKB_RN42_ENABLE = yes` persisted in `rules.mk` and correctly triggered the inclusion of the RN42 C files.

---

### Phase 2: The Modern Transition

#### **v0.22.0 → v0.28.0 (The Stability Plateau)**
*   **Status:** Consistently Successful
*   **Firmware Size:** Fluctuated slightly around ~23.5KB - 23.8KB.
*   **Critical Fix (System Environment):** **Python 3.14 Compatibility**.
    *   **Issue:** Starting during this era, modern Python environments deprecated `ast.Num` in favor of `ast.Constant`. QMK's internal CLI scripts (specifically `lib/python/qmk/math.py`) would crash immediately during `make` on your system.
    *   **Fix:** We applied a persistent patch using `sed` to replace `isinstance(node, ast.Num)` with `isinstance(node, ast.Constant)`. This patch had to be re-verified or re-applied after certain version jumps where the file was touched by upstream.
*   **Build System Evolution:**
    *   **Data Driven Config (`info.json`):** QMK began introducing `info.json` during this period.
    *   **Observation:** In these intermediate versions, `info.json` existed but the build system was permissive. It allowed our legacy `rules.mk` approach (which manually adds C files) to function without needing to explicitly delete `info.json`.
    *   **Conflict Resolution:** We encountered occasional git conflicts in `rules.mk` (specifically at v0.28.0). These were resolved by prioritizing our custom "Ours" version of the build rules to preserve the `RN42_DIR` definitions, while accepting upstream changes for the platform/core libraries.

---

### Phase 3: Breaking Changes & Recent History

#### **v0.29.0**
*   **Status:** Successful
*   **Firmware Size:** 23,932 bytes
*   **Critical Issue:** `info.json` conflict.
    *   QMK introduced a detailed `info.json` for HHKB.
    *   **Fix:** We executed `git rm keyboards/hhkb/ansi/info.json`. We **must** use `rules.mk` to define `SRC += $(RN42_DIR)/...`, which `info.json` cannot currently handle for this specific mod.
*   **Python:** Continued patching `lib/python/qmk/math.py`.

#### **v0.30.0**
*   **Status:** Successful
*   **Firmware Size:** 23,954 bytes
*   **Critical Issue:** Keycode Migration.
    *   **Error:** `KC_BTN1`, `KC_MS_U`, `KC_ACL1` etc. were removed from the codebase.
    *   **Fix:** Updated `keyboards/hhkb/ansi/keymaps/schaeferdev/keymap.c` to use new standard defines:
        *   `KC_BTN1` -> `MS_BTN1`
        *   `KC_MS_U` -> `MS_UP`
        *   `KC_ACL0` -> `MS_ACL0`
    *   **Legacy Mode:** Continued deleting `info.json`.

#### **v0.31.0**
*   **Status:** Successful
*   **Firmware Size:** 24,090 bytes
*   **Critical Issue:** Merge Conflict in `math_ops.py`.
    *   **Fix:** QMK finally updated their python scripts to support `ast.Constant` and renamed the module to `math_ops.py`.
    *   **Action:** We accepted the "Incoming/Upstream" version of `lib/python/qmk/math_ops.py`.
    *   **Cleanup:** The old `lib/python/qmk/math.py` became obsolete. It was left as an untracked file and subsequently deleted to avoid confusion.
    *   **Legacy Mode:** Continued deleting `info.json`.

#### **v0.31.8 (Latest Stable)**
*   **Status:** Successful
*   **Firmware Size:** 28,668 bytes (99% - CRITICAL)
*   **State:**
    *   Custom RN42 files present.
    *   `info.json` removed.
    *   `keymap.c` updated for v0.30+ standards.
    *   **New Architecture:**
        *   **Build Logic:** Moved RN42 source inclusion from `keyboards/hhkb/ansi/rules.mk` to `keyboards/hhkb/ansi/post_rules.mk` to ensure keymap flags (`HHKB_RN42_ENABLE`) are respected.
        *   **Driver Patch:** Updated `rn42.c` to match the new `host_driver_t` struct (inserted `NULL` for `send_nkro`).
        *   **Dependencies:** Added `#include <stddef.h>` to `rn42.c`.

#### **v0.31.8 (Final Configuration & Fixes)**
*   **Status:** Successful & Functional
*   **Modernization:**
    *   **Info.json:** Re-created `keyboards/hhkb/ansi/info.json` to be fully compliant with QMK 0.31.8 standards (replacing the deletion hack).
    *   **Legacy Cleanup:** Purged deprecated options from `rules.mk` and `config.h`.
*   **Critical Fix (RN42 Bluetooth):**
    *   **Issue:** The RN42 module commands were failing because `config.h` was cleaned too aggressively, removing hardware UART settings.
    *   **Fix:** Restored `SERIAL_UART_BAUD 115200` and `SERIAL_UART_INIT_CUSTOM` in `config.h` to enable RX interrupts for the bluetooth module.
    *   **Patch:** Modified `keyboards/hhkb/rn42/serial_uart.c` to defer initialization to the custom macro in `config.h`.

---

## Migration Cheat Sheet (For Future Reference)

If you need to migrate to **0.32.0** or later, follow these steps:

1.  **Stash Custom Files:**
    ```bash
    git stash -u  # -u includes untracked files like keymaps/schaeferdev
    ```

2.  **Checkout New Version:**
    ```bash
    git checkout <new_version_tag>
    ```

3.  **Pop Stash & Resolve:**
    ```bash
    git stash pop
    ```
    *   *If `info.json` has conflicts*: Delete it. Use `git rm keyboards/hhkb/ansi/info.json`.
    *   *If `math.py` has conflicts*: Accept "Theirs/Upstream" (likely they fixed it).

4.  **Verify Rules:**
    Ensure `keyboards/hhkb/ansi/post_rules.mk` exists and contains:
    ```makefile
    ifeq ($(strip $(HHKB_RN42_ENABLE)), yes)
        OPT_DEFS += -DHHKB_RN42_ENABLE
        RN42_DIR = keyboards/hhkb/rn42
        SRC += $(RN42_DIR)/serial_uart.c \
               # ...
    endif
    ```

5.  **Compile:**
    ```bash
    make hhkb/ansi:schaeferdev
    ```
