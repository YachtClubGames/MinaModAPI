# Building the example mods

The included `CMakeLists.txt` builds every example in `examples/` as a
ready-to-use mod: each one is compiled to `mod.dll` (Windows) or `mod.so`
(Linux) with a generated `mod.yc` manifest next to it, matching the folder
layout the game expects.

## Requirements

* CMake 3.15+
* A C++11 compiler
  * Windows: Visual Studio 2019+ (MSVC), or clang/MinGW
  * Linux: GCC or Clang

## Build

```sh
cmake -B build
cmake --build build --config Release
```

The mods end up in `build/mods/`:

```
build/mods/
  basic/
    mod.dll (or mod.so)
    mod.yc
  hp_bars/
    ...
```

## Install into the game

Copy the folders from `build/mods/` into the game's mods folder, or use the
provided deploy target:

```sh
cmake --build build --config Release --target deploy
```

The mods folder is:

* Windows: `%APPDATA%\Yacht Club Games\Mina the Hollower\mods`
* Linux: `~/.local/share/Yacht Club Games/Mina the Hollower/mods`

Then run the game with:

```
-mod -mod-allow-code
```

Check `mod.log` next to the mods folder if something doesn't load.

## The mod.yc manifest

The generated manifest looks like this:

```
[YCD Version: 1]
MinaModDef
{
	id: "my_mod",
	name: "My Mod",
	modVersion: 1,
	minGameVersion: 0,
	maxGameVersion: 0,
	loadPriority: 0,
}
```

* `id` / `name` — identifier and display name.
* `modVersion` — your mod's own version number.
* `minGameVersion` / `maxGameVersion` — inclusive range of game revisions the
  mod accepts. `0` means "no constraint"; a mod outside the range is skipped
  with "Mod failed version check." in `mod.log`.
* `loadPriority` — load order relative to other mods.

## Writing a cross-platform mod

Export the entry point with the `MM_EXPORT` macro from `MinaModAPI.h` instead
of `__declspec(dllexport)` so the same source builds on both platforms:

```cpp
#include "MinaModAPI.h"

extern "C"
MM_EXPORT
void MinaMod_Init( MinaModAPI* mm )
{
    // ...
}
```
