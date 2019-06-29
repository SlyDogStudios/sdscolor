sdscolor
Author: Robert L. Bryant
http://slydogstudios.org
slydogstudios@gmail.com


====================================================================
WHAT THIS PROGRAM DOES                                              |
====================================================================
Changes one color to another color in an NES tileset. The user also |
decides which tiles they want this to happen on.                    |
====================================================================


====================================================================
COMPILING                                                           |
====================================================================
I use the GNU compiler for C++, g++. With this, it should build no  |
problem.                                                            |
                                                                    |
Windows: g++ -o sdscolor.exe sdscolor.cpp                           |
====================================================================


====================================================================
PLATFORMS                                                           |
====================================================================
This program has been compiled, tested, and confirmed to work on:   |
                                                                    |
Windows 8                                                           |
====================================================================


====================================================================
DISCLAIMER                                                          |
====================================================================
I hold no responsibilities for this program doing anything to your  |
computer that is considered undesirable. You can use/modify the     |
source all you want, pass it on, etc. I have no beef with that at   |
all. If you do use the source for a project that you do, a simple   |
nod in my direction would be nice, but not necessary :)             |
====================================================================


====================================================================
USAGE                                                               |
====================================================================
The program can be used rather simply. It is terminal driven, which |
means you will have to pull up your command-line to use it. The     |
command to use the program is:                                      |
                                                                    |
sdscolor <file> <firstTile> <lastTile> <colorToReplace> <newColor>  |
                                                                    |
The breakdown for this is:                                          |
                                                                    |
sdscolor                                                            |
    This is the name of the program obviously. If you compiled it   |
    yourself and named it something different, you will have to     |
    use that name.                                                  |
                                                                    |
<file>                                                              |
    This is the name/location of the file that you want to change   |
    the colors of the tiles in. It will be both opened and written  |
    to. If you desire to make a backup, you will have to do that    |
    manually before running this program.                           |
                                                                    |
<firstTile>                                                         |
    The number of the first tile that you want to have affected.    |
    Use a hexadecimal number with no '$', '0x', or 'h' attached.    |
                                                                    |
<lastTile>                                                          |
    The number of the last tile that you want to have affected.     |
    Use a hexadecimal number with no '$', '0x', or 'h' attached.    |
                                                                    |
<colorToReplace>                                                    |
    The number of the palette color that you want to replace.       |
    0, 1, 2, or 3 are appropriate data to enter here.               |
                                                                    |
<newColor>                                                          |
    The number of the new palette color that you want to take the   |
    place of the colorToReplace. 0, 1, 2, or 3 are appropriate data |
    to enter here.                                                  |
                                                                    |
An example of using the program:                                    |
                                                                    |
sdscolor myCHR.chr 30 5f 1 2                                        |
                                                                    |
    This will replace palette color 1 with palette color 2, in      |
    tiles $30-$5f of the file named myCHR.chr.                      |
                                                                    |
====================================================================


====================================================================
FUTURE VERSIONS                                                     |
====================================================================
I don't know if there will actually be any future versions of this  |
or not. The only other thing I might like to add is an extra        |
argument to make a backup version of the file before writing to the |
original.                                                           |
====================================================================

EOF