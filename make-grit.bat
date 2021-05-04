@echo off

:: allow local variable 'name'
SETLOCAL ENABLEDELAYEDEXPANSION

:: for each '.png' file in 'dir/images', create a '.grit' file if it doesn't already exist
for /r %%a IN ("images\*.png") do (
    :: set 'name' to the filename without the extension
    set name=%%~na
    
    :: create empty 'name.grit' file
    if not exist images\!name!.grit type nul >images\!name!.grit
)

:: for each '.grit' file in 'dir/images', delete it if the corresponding '.png' file doesn't exist
for /r %%b IN ("images\*.grit") do (
    :: set 'name' to the filename without the extension
    set name=%%~nb

    :: if 'name.'png' DNE delete 'name.grit'
    if not exist images\!name!.png del images\!name!.grit
)

:: make .grit files for sprites and bgs, and add folders to images for them