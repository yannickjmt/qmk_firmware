### XD75 keymap by Yannick

#### Mac and Windows base layers
* [x] hold caps lock => function layer
* [x] tap right shift => ;
* [x] tap dance on leftmost and rightmost bottom row buttons to change workspace
  - single tap = mod tap
  - hold = mod
  - double tap = next/prev desktop
  - triple tap = move 2 desktops at once


#### function layer :
* [x] F2-F12 on num row
* [x] !@#$%+^&*() on corresponding letter row
* [x] LED control
* [x] change default layer
* [x] dfu
* [x] dynamic macros

#### numpad layer :
* [x] numpad on right side
* [x] brackets on left side
* [x] double tap toggle

#### nav layer :
* [x] tap layer => mods are "one shot mods"
* [x] hold layer => mods behave normally
* [x] nav on right side
* [x] invert mods CTRL/GUI depending on base layer
* [x] alt-tab macro
* [x] email adresses
* [x] Excel shortcut on macros
    * [x] ctrl+alt+V V
    * [x] left ctrl+down right ctrl+shift+up ctrl+D

#### french layer:
* [x] accented chars, some greek and mathematical signs, disposition inspired by qwerty-fry
  - needs Wincompose on windows

#### emails
secret.h is in git/info/exclude
To include the emails at compile time, add them in secret.h and include the flag `IS_YANNICK` in the cmd:

```
make xd75:yannick:dfu EXTRAFLAGS=-DIS_YANNICK
```
