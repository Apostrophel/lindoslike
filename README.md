# Setting up QMK to flash Keychron Q2 Pro

## Overview
Since Q2 Pro is *wireless*, it is necessary to use the `wireless_playground` branch of the Keychron fork of QMK. This must be downloaded to get the default QMK keyboard layout for the keyboard. The steps to get on `wireless_playground` is described below.

## Steps to get the default keymap
1. Install QMK normally. https://docs.qmk.fm/newbs_getting_started
2. Fetch the Keychron fork, but only extract the specific "Q2 Pro" keyboard definition:
```shell
git -C ~/qmk_firmware remote add keychron https://github.com/Keychron/qmk_firmware.git

git -C ~/qmk_firmware fetch keychron

git checkout keychron/wireless_playground -- keyboards/keychron/q2_pro
```
The current branches/forks can be checked by `git -C ~/qmk_firmware/ remote -v`. Check if the download worked by seeing if the `q2_pro/` directory appeared in the keychron keyboard folder in the qmk_firmware. 

After these steps, the keymap-folder `lindoslike` here should be placed in the `iso_encoder/layouts/keymaps/` folder.

## Editing and flashing the keymap 
To change the layout, layers, combo keys and more, edit `keymap.c`. To flash the Q2 Pro keyboard, navigate to the root QMK folder `qmk_firmware/`, make sure that the correct layout and keyboard is set as default (See QMK Docs). Then,
```
qmk compile
qmk flash
```

While the flash command is running, turn off the Q2 Pro, hold down the ESC key, and turn it back on. The keyboard should now flash the new build.

## Troubleshooting
Honestly, I stooped to troubleshoot the QMK wireless stuff with AI-assistance. Here is the AI-written troubleshooting steps, just to be able to compile the keymap... 

### Step 1 — Switch to Keychron's wireless_playground branch

If the keyboard is not recognized by QMK (e.g. `invalid keyboard_folder` errors), the full Keychron fork is needed rather than just the extracted folders. Also update the Python dependencies for the new branch:
```shell
git -C ~/qmk_firmware checkout keychron/wireless_playground
/home/sjur/.local/share/uv/tools/qmk/bin/python -m pip install -r ~/qmk_firmware/requirements.txt
```

### Step 2 — Sync submodules

The submodules (ChibiOS etc.) must match Keychron's branch, otherwise you will get linker errors about missing symbols like `__core_init`:
```shell
cd ~/qmk_firmware
git submodule update --init --recursive
```

### Step 3 — Fix missing eeconfig_language.h include path

Keychron's `wireless_playground` branch has a bug where `eeconfig_kb.h` includes `eeconfig_language.h` but the file has since moved into a `language/` subdirectory. Fix the include path directly:
```shell
sed -i 's/#include "eeconfig_language.h"/#include "language\/eeconfig_language.h"/' \
    ~/qmk_firmware/keyboards/keychron/common/eeconfig_kb.h
```

### Step 4 — Fix EECONFIG_KB_DATA_SIZE redefinition

Keychron's `eeconfig_kb.h` redefines `EECONFIG_KB_DATA_SIZE` without an `#ifndef` guard, conflicting with upstream QMK's definition. Wrap it:
```shell
sed -i 's/#define EECONFIG_KB_DATA_SIZE (EECONFIG_END_WIRELESS_CONFIG - EECONFIG_BASE_LANGUAGE)/#ifndef EECONFIG_KB_DATA_SIZE\n#define EECONFIG_KB_DATA_SIZE (EECONFIG_END_WIRELESS_CONFIG - EECONFIG_BASE_LANGUAGE)\n#endif/' \
    ~/qmk_firmware/keyboards/keychron/common/eeconfig_kb.h
```

### Step 5 — Fix debounce double definition

Keychron's custom debounce driver conflicts with QMK's built-in one unless you explicitly tell QMK to use a custom debounce type. Add this to your keymap's `rules.mk`:
```shell
echo "DEBOUNCE_TYPE = custom" >> ~/qmk_firmware/keyboards/keychron/q2_pro/iso_encoder/keymaps/<your_keymap_name>/rules.mk
```

---

> **Note:** Steps 3–5 are patches for bugs in Keychron's `wireless_playground` branch. If Keychron updates their branch these may no longer be needed, so it is worth trying a clean compile before applying them.
