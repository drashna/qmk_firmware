

# USB-to-USB convertor using [Adafruit RP2040 USB Host](https://www.adafruit.com/product/5723)

This is based on [Sekigon's Keyboard Quantizer mini-full branch](https://github.com/sekigon-gonnoc/qmk_firmware/tree/keyboard/sekigon/keyboard_quantizer/mini-full/keyboards/sekigon/keyboard_quantizer/mini) and [GongYiLiao's branch supporting the Adafruit RP2040 with USB Host](https://github.com/GongYiLiao/qmk_AdaFruitRp2040USBH) and incorporates updates from [raghur's audio-keys project](https://github.com/raghur/adafruit_rp2040_usbh/tree/audio-keys). 

This is for QMK 0.24. I have not updated it for newer builds. However, raghur's change's have removed the prior vendor dependences. This now works with the latest tinyUSB and PICO-PIO-USB distributions, with the tested distrubtions as submodules. 

## Available keymaps

A new custom layout for the Tartarus V2 has been developed.

This distribution is generic, and includes layouts and generic keymaps for :
* Generic Full Size ANSI 104 layout under `keymaps/default`
* Razer Tartarus V2 under `keymaps/tartarus2`

## How to use this repository

Install using the normal guide: [setup your qmk envorinment](https://github.com/qmk/qmk_firmware/blob/master/docs/newbs_getting_started.md). This will install the latest version of QMK. 

Then run the following:
```
git checkout 0.24.0 -b qmk-0.24.0
git submodule update --init --recursive
```
This will install QMK 0.24. This is a requisite step. Don't skip it.

After clone this repository to `keyboards/converter` then run

```
git clone https://github.com/whyaaronbailey/adafruitrp2040_usbh.git _your_qmk_repo/keyboards/converter/adafruit_rp2040_usbh
cd _your_qmk_repo/keyboards/converter/adafruit_rp2040_usbh
git submodule update --init --recursive
cd ../../..
make converter/adafruit_rp2040_usbh:_your_choice:uf2 
```

where `_your_choice` can be `default` for generic 104-key Fullsize ANSI keyboard and `tartarus2` for the Razer Tartarus V2. If you want to use my PACs distribution, use `taratus2_pacs`.


## TODO:
* Improve documentation
* Scroll wheel and scroll click customization (need to implement additional interfaces)
* LED light control
