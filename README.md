# Setting up QMK to flash Keychron Q2 Pro

## Overview
Since Q2 Pro is *wireless*, the `wireless_playground` branch of the Keychron fork of QMK. This must be downloaded to get the default QMK keyboard layout for the keyboard.

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
