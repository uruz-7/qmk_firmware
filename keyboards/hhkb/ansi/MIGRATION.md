# RN42 Bluetooth Support Migration Notes

## Summary of Fixes (Feb 2026)

To restore functionality for the RN42 Bluetooth module (Hasu's Alt Controller mod) in modern QMK (0.31.8+), the following changes were required. The original implementation relied on legacy defaults that are no longer compatible or were missing critical configuration macros.

### 1. `config.h` Restoration
The following macros were re-added to `keyboards/hhkb/ansi/config.h` (guarded by `#ifdef HHKB_RN42_ENABLE`). These are critical for communication with the RN42 module.

*   **Software UART Pins**: `SUART_OUT_PORT`, `SUART_OUT_BIT`, `SUART_IN_PIN`, `SUART_IN_BIT`.
*   **Hardware UART Configuration**:
    *   `SERIAL_UART_BAUD 115200`: The default was 9600, but the RN42 module is configured for 115200bps.
    *   `SERIAL_UART_INIT_CUSTOM`: Custom initialization block. This is **critical** because the standard `serial_uart.c` initialization did not enable the RX Interrupt (`RXCIE1`) or the Receiver (`RXEN1`) correctly for this specific hardware setup, causing the keyboard to ignore all incoming data from the bluetooth module.
    *   `SERIAL_UART_RTS_LO` / `SERIAL_UART_RTS_HI`: Flow control macros.

### 2. `serial_uart.c` Patch
The file `keyboards/hhkb/rn42/serial_uart.c` was patched to prevent it from overwriting the baud rate registers initialized by `SERIAL_UART_INIT_CUSTOM`.

### 3. Build System
The `info.json` now handles the core keyboard configuration, but `rules.mk` in the keymap (e.g., `schaeferdev`) must still specify:
```makefile
HHKB_RN42_ENABLE = yes
```
This triggers `post_rules.mk` to include the RN42 driver files and define the `HHKB_RN42_ENABLE` macro.
