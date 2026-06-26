!!!!!!!!!!
!! All modding functionality is experimental and subject to change!
!!
!! Using modded files could be dangerous! Treat modded files the same as you
!! would downloading an .exe file!
!!!!!!!!!!

	Modding functionality is currently in the "experimental-modding" branch
	on Steam, the password is 'modsmodsmods'

Mods live in a folder at %appdata%\Yacht Club Games\Mina the Hollower\mods
* Each mod has a separate folder.
* Each mod contains a mod.yc file which contains some basic information about
  the mod (name, load priority, min/max game version)
* Each mod can contain a 'data' folder, files in this folder will be loaded in
  place of default game files.

To enable modding support you must run with the `-mod` command line argument.

Mods can load files from a text based format instead of the binary files the
game ships with. To generate a sample mod full of these files, run the game
with the arguments `-mod -unpak`.

	Make sure to remove the `-unpak` argument after this is done!

This will generate an 'unpak' mod in your mods folder, which contains text
versions of all of the game's data. When you start the game with `-mod` this
copy of the data will be loaded!

It can be slow to load files in this form, for a real mod you should only
include modified files, instead of _all_ of the game's files.

	To remove this mod delete the `unpak` folder in your mods folder.

A mod.log file will be generated in %appdata%\Yacht Club Games\Mina the Hollower
which contains basic information about which mods are loaded, and errors if
they occur.

Other arguments:

-mod-log-verbose
  Enable printing additional information to the log, including any time a file
  replacement occurs.

-mod-allow-code
  If a mod contains a mod.dll, load it. If the mod exposes a function named
  MinaMod_Init it will be called and passed a MinaModAPI pointer.
