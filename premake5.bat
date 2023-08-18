@echo off

set PREMAKE_PATH=.\vendor\premake\.premake\

.\vendor\premake\premake5.exe %1 %2

@echo on