# Hart
A game engine being built in C++ and OpenGL 4.6 <br>

## Info 
I'm making this engine as a learning exercise. As such I probably won't be accepting any pull requests.<br>
(That is if someone somehow finds this repository lol)

## Build System
CMake

## Dependencies
* [glfw](https://www.glfw.org/): For Windowing, Creating OpenGL Context, Input handling, etc.
* [glad](https://glad.dav1d.de/): For accessing OpenGL functions.
* [stb](https://github.com/nothings/stb): Specifically [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) for loading images.<br>
* [miniaudio](https://miniaud.io/): For audio

## Build Instructions
First clone the repo using the command
```
git clone --recursive https://github.com/Hemanth3303/Hart.git
```
Then cd to that directory
```
cd Hart
```

Then follow the instructions for your os

* Windows
```
cmake -S . -B build
cmake --build build -j6
cd .\build\Debug
.\Sandbox.exe
```

* Linux
```
cmake -S . -B build
cmake --build build -j6
cd ./build/Debug
./Sandbox
```

You can also use any of the predefined cmake presets, `use cmake --list-presets` to view them.

## Credits for Assets used in Sandbox
* SpriteSheet: [RPG_Base](https://www.kenney.nl/assets/rpg-base)
* Music: [CriticalTheme](https://not-jam.itch.io/not-jam-music-pack)

## Note
Heavily inspired by the [TheCherno](https://www.youtube.com/@TheCherno)'s [Sparky Engine series](https://youtube.com/playlist?list=PLlrATfBNZ98fqE45g3jZA_hLGUrD4bo6_&si=7wCTJJ7dkz3_YiHU) and [Hazel Game Engine](https://youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&si=DDBFTAqIOJZEUX0i) series <br>
