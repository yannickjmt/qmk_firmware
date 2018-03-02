# Yannickjmt's TADA68 layout

A few modifications of the default layout, and an additional layer cointaining a numpad

* Add mac media control buttons
* Remap right ctrl tap to Home, double tap to End
* Moved arrows in function layer from WASD to ESDF
* Function layer accessible caps lock hold, or caps lock double tap
* Added numpad layer accessible with fn btn toggle
* Double tap left Ctrl = caps lock

TODO : 
* can use space cadet for shift to open and close parenthesis
* or one tap right shift = hold alt
* Add email macro. screen cap macro?
* Adding a power (`KC_POWER`) key, so the lock screen shortcut works.

* changing caps lock led position https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/gamenum/README.md
https://www.reddit.com/r/olkb/comments/7cljop/qmk_using_an_in_switch_led_as_an_indicator_frosty/
https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

    adding led toggle on and off with layer activationn

cf maartenwut :
* can use lshift as  "one shot key"
#define LSHIFT OSM(MOD_LSFT)


