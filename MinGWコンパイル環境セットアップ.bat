@echo OFF
title MinGW-gcc
echo MinGW-gccのディレクトリにパスを通します 
path C:\Program Files\CodeBlocks\MinGW\bin;%PATH%
rem path
echo ------- gcc check ------------
gcc -v
rem pause
echo ------------------------------
cmd.exe