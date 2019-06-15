# XD75 keymap by Yannick

Mac and Windows base layers
[x] hold caps lock => function layer
[x] tap right shift => ;
[x] tap dance on leftmost and rightmost bottom row buttons to change workspace (ctrl left/right on mac, ctrl+win left/right on windows)
    single tap = mod tap
    hold = mod
    double tap = next/prev desktop
    triple tap = move to desktop after or before next/prev desktop
[x] windows base layer 
    with inverted left ctrl and lgui keys


function layer :
[x] F2-F12 on num row
[x] !@#$%+^&*() on corresponding letter row
[x] LED control
[x] change default layer


numpad layer :
[x] numpad on right side
[x] brackets on left side
[x] double tap toggle

nav layer :
[x] nav on right side
[x] one shot mods on left side
    [x] invert one shot mods CTRL/GUI depending on base layer
[x] alt-tab or cmd-tab macro depending on base layer
[x] email adresses
[ ] one tap layer mod?
[x] Excel shortcut (windows only)
    [x] ctrl+alt+V V
    [x] left ctrl+down right ctrl+shift+up ctrl+D

french layer:
[x] accented chars, some greek and mathematical signs, disposition inspired by qwerty-fry
    needs on MACOS "unicode hex input" as keyboard preference
    needs Wincompose on windows. 

secret.h is in git/info/exclude
To include the emails at compile time, add them in secret.h and include the flag `IS_YANNICK` in the cmd:

```
make xd75:yannick:dfu EXTRAFLAGS=-DIS_YANNICK
```
