# electricsheep-hd-windows-scr
Windows screensaver for electricsheep-hd 

# How to build?
This is a writedown from memory. It might be lacking some crucial steps:

- Install MSYS2 (http://www.msys2.org/)
- start MSYS2
- pacman -S git mingw-w64-x86_64-gcc mingw-w64-x86_64-mpv
- download mpv _dev_ build (https://mpv.srsfckn.biz/)
- sync include dir from dev build to $MSYS/usr/include
- switch to mingw64.exe
- run ./build.sh
