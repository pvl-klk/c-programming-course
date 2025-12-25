@echo off

gcc list_array.c sorted_list.c -o main.exe
main.exe
del main.exe

echo:
pause
cls
