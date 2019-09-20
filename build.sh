#!/bin/sh
binary="eshd.exe"
#wget -N -O mpv-dev-latest.7z "https://mpv.srsfckn.biz/mpv-dev-latest.7z" 
gcc.exe -v -L /usr/include/ -o $binary eshd.c -lmpv
mkdir -p build
cp $binary build/eshd.exe
cp $binary "build/Electric Sheep HD.scr"
cp $binary "/c/Windows/System32/Electric Sheep HD.scr"
zip build/eshd-scr.zip build/eshd.scr build/mpv-1.dll
