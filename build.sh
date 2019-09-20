#!/bin/sh
binary="eshd.exe"
gcc.exe -v -L /usr/include/ -o eshd.exe eshd.c -lmpv
mkdir -p build
cp $binary build/eshd.exe
cp $binary build/eshd.scr
cp $binary /c/Windows/System32/eshd.scr
