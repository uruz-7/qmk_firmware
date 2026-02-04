 # QMK HHKB Keymap: uruz7z

This is my QMK keymap for the Happy Hacking Keyboard Pro 2 alternate controller made by Hasu.

## Setup
```bash
curl -fsSL https://install.qmk.fm | sh
sudo apt-get install gcc-avr 
git submodule update --init --recursive
```

## Flashing

```bash
make clean
make hhkb:uruz7z
make hhkb:uruz7z:dfu
```
