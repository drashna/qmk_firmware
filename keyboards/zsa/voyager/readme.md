# Voyager

![Voyager](https://zsa.io/static/gallery-white-case-7a2ef555f8f7f4ce1b9030477b16e517.png)

A next-gen split, ergonomic keyboard with an active left side, USB type C, integrated wrist rest, and a thumb cluster that can move.

* Keyboard Maintainer: [drashna](https://github.com/drashna), [ZSA](https://github.com/zsa/)
* Hardware Supported: Voyager (STM32F303xC)
* Hardware Availability: [ZSA Store](https://zsa.io/voyager/)

Make example for this keyboard (after setting up your build environment):

    make zsa/voyager:default

Flashing example for this keyboard:

    make zsa/voyager:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Voyager Customization

### Indicator LEDs

There are 6 functions for enabling and disabling the LEDs on the top of the boards. The functions are `ML_LED_1(bool)` through `ML_LED_6(bool)`, with the first LED being the left most LED on the left hand, and the sixth LED being the right most LED on the right side. 

By default, the Indicator LEDs are used to indicate the layer state for the keyboard.  If you wish to change this (and indicate caps/num/scroll lock status instead), then define `VOYAGER_USER_LEDS` in your `config.h` file. 

### Detecting split / Gaming mode

To make it extra gaming friendly, you can configure what happens when you disconnect the right half. This is especially useful when using gaming unfriendly layers or layouts (e.g. home row mods, dvorak, colemak).

Example for enabling a specific layer while right side is disconnected:

```
void housekeeping_task_user(void) {
    if (!is_transport_connected()) {
        // set layer
    }
}
```
