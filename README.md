# Hart
A (mostly 2d) game engine built in C++ and OpenGL 4.6 <br>

## Important Note
- Please do not use this as a reference for code structure, C++, OpenGL or engine architecture.
- If you want a proper reference, use Cherno's Hazel2D instead, [linked below](#note).

## Info
I made this engine as a learning exercise. As such I won't be accepting any pull requests.<br>
(That is if someone somehow finds this repository)

## Build System
CMake

## Dependencies
* [glfw](https://www.glfw.org/): For Windowing, Creating OpenGL Context, Input handling, etc.
* [glad](https://glad.dav1d.de/): For accessing OpenGL functions.
* [stb](https://github.com/nothings/stb):
  * [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for loading images.
  * [stb_truetype](https://github.com/nothings/stb/blob/master/stb_truetype.h) for loading ttf fonts
* [miniaudio](https://miniaud.io/): For audio

## Build Instructions

First clone the repo recursively.

#### Note: This engine builds **GLFW** from source at `vendor/glfw`. For required development libraries and tools depending on your OS, see **[GLFW’s compile guide](https://www.glfw.org/docs/latest/compile.html)** and install what CMake reports as missing.

### Windows example
Specify a generator manually like so:
```bash
$ cmake -S. -Bbuild -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ .\build\windows_x86-64\Debug\Sandbox.exe
```
Or use a predefined preset. <br>
For example, to use gcc and makefiles for a debug build on windows x86-64:
```bash
$ cmake --preset=windows_x86-64_debug_mingw-w64_makefiles
$ cmake --build build
$ .\build\windows_x86-64\Debug\Sandbox.exe
```

### Linux example

Specify a generator manually like so:

```bash
$ cmake -S. -Bbuild -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ ./build/linux_x86-64/Debug/Sandbox
```
Or use a predefined preset. <br>
For example, to use gcc and makefiles for a debug build on linux x86-64:
```bash
$ cmake --preset=linux_x86-64_debug_gcc_makefiles
$ cmake --build build
$ ./build/linux_x86-64/Debug/Sandbox
```

Note: Use `cmake --list-presets` to see all available presets


## Credits for Assets used in Sandbox
* SpriteSheet: [RPG_Base](https://www.kenney.nl/assets/rpg-base)
* Music: [CriticalTheme](https://not-jam.itch.io/not-jam-music-pack)

## Note
Heavily inspired by the [TheCherno](https://www.youtube.com/@TheCherno)'s [Sparky Engine series](https://youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_&si=7wCTJJ7dkz3_YiHU) and [Hazel Game Engine](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=DDBFTAqIOJZEUX0i) series <br>

The font rendering was implemented based on tutorial and code in [this article](https://dev.to/shreyaspranav/how-to-render-truetype-fonts-in-opengl-using-stbtruetypeh-1p5k).
