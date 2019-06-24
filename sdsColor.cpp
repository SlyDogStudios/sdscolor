// ************************************************************************	//
//                                                                          //
// Program : sdscolor                                                       //
// Task: Change one palette color to another palette color in a user-       //
//  defined set of tiles of an NES CHR file                                 //
// Programmer: Robert L. Bryant	(slydogstudios@gmail.com)                   //
//                                                                          //
// ************************************************************************ //

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

using namespace std;

const unsigned short int COLOR_LO[4] = {0, 1, 0, 1};
const unsigned short int COLOR_HI[4] = {0, 0, 1, 1};
const unsigned short int ARGUMENT_LENGTHS[6] = {0, 0, 2, 2, 1, 1};
const char *ARGUMENT_OFFSETS[] = {"0", "0", "f", "f", "3", "3"};
const char *ARGUMENT_NAMES[] = {"Executable", "File Name", "First tile", "Last tile", "Color to replace", "New Color"};
const string ENDING = "Terminating program.";

struct stat results;

int main(int argc, char* argv[])
{
	unsigned short int PAL0_SET[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned short int PAL1_SET[16] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned short int PAL2_SET[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	unsigned short int PAL3_SET[16] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	unsigned short int PAL_CLR[16] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe, 0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
	unsigned short int whichBit[8] = {7, 6, 5, 4, 3, 2, 1, 0};
	stringstream arg_data[6];
	int arg_conv[6];
	int fileSize;
	unsigned short int incrementer = 0;
	unsigned short int *tableSet;
	unsigned short int gotOne = 0;

// If there aren't enough arguments, output the program usage.

	if (argc != 6)
	{
		cout << "\n  Usage: " << argv[0] << " <file>";
		cout << " <first tile>" << " <last tile>";
		cout << " <color to replace>" << " <new color>\n" << endl;
		cout << "  First tile/last tile: hex 00 to FF." << endl;   
		cout << "    Do not prefix with '0x' or '$' and do not append with 'h'. " << endl;
		cout << "\n  Color to replace/new color: integer 0-3." << endl;
		cout << "\n  Example:" << endl;
		cout << "\n    sdscolor myCHR.chr 30 5f 1 2" << endl << endl;
	}
	else                         // If there are the right amount of arguments, check for correct inputs
	{
		for (int i = 2; i < 6; i++)
		{
			string convertArg;
			convertArg = argv[i];
			if ((convertArg.length() < ARGUMENT_LENGTHS[i]) || (convertArg.length() > ARGUMENT_LENGTHS[i]))
			{
				cout << "\n    Wrong length of input for command line argument " << i;
				cout << " (" << ARGUMENT_NAMES[i] << ")." << endl;
				cout << "    " << ENDING << endl;
				return 0;
			}
			for (int j = 0; j < ARGUMENT_LENGTHS[i]; j++)
			{
				char ch;
				ch = convertArg[j];
				if ((ch < '0') || (ch > *ARGUMENT_OFFSETS[i]))
				{
					if (i < 4)
						cout << "\n    Use only hex digits for tile offsets." << endl;
					else
						cout << "\n    Use only 0, 1, 2 or 3 for palette selections." << endl;
					cout << "    " << ENDING << endl;
					return 0;
				}
			}

			arg_data[i] << convertArg;
			arg_data[i] >> hex >> arg_conv[i];
		}

		if (arg_conv[2] >= arg_conv[3])
		{
			cout << "\n    First tile number cannot be the same or more than the last tile." << endl;
			cout << "    " << ENDING << endl;
			return 0;
		}

		if (arg_conv[4] == arg_conv[5])
		{
			cout << "\n    Color to replace cannot be the same as the new color." << endl;
			cout << "    " << ENDING << endl;
			return 0;
		}

		int firstTileOffset = arg_conv[2] * 16;
		int lastTileOffset = arg_conv[3] * 16;
		int smallerThanFile = lastTileOffset + 16;

		fstream inFile (argv[1], ios::in | ios::out | ios::binary);

		if (!inFile.is_open())
		{
			cout << "\n    File does not exist." << endl;
			cout << "    " << ENDING << endl;
			return 0;
		}
		else
		{
			if (stat(argv[1], &results) == 0)
				fileSize = results.st_size;
			if (smallerThanFile > fileSize)
			{
				cout << "\n    Last tile will write beyond the file size." << endl;
				cout << "    " << ENDING << endl;
				inFile.close();
				return 0;
			}
		}

// Get the file contents

		unsigned char dataIn[fileSize];
		inFile.seekg(firstTileOffset, ios::beg);

		for(int z = firstTileOffset; z < smallerThanFile; z++)
		{
			char x;
			inFile.get(x);
			dataIn[z] = x;
		}

// Point at the correct table to use for replacing the color
		switch (arg_conv[5])
		{
			case 0:
				tableSet = PAL0_SET;
				break;
			case 1:
				tableSet = PAL1_SET;
				break;
			case 2:
				tableSet = PAL2_SET;
				break;
			case 3:
				tableSet = PAL3_SET;
		}

		inFile.seekg(firstTileOffset, ios::beg);

// Begin searching the data pulled out of the file and manipulating the bits
//  as needed
		for(int q = firstTileOffset; q < smallerThanFile; q++)
		{

			for(int r = 0; r < 8; r++)
			{

				if ((((dataIn[q] >> whichBit[r]) & 1) == COLOR_LO[arg_conv[4]]) && (((dataIn[q+8] >> whichBit[r]) & 1) == COLOR_HI[arg_conv[4]]))
				{
					gotOne = 1;

					if (COLOR_LO[arg_conv[5]] == 1)
						dataIn[q] |= tableSet[r];
					else
						dataIn[q] &= PAL_CLR[r];

					if (COLOR_HI[arg_conv[5]] == 1)
						dataIn[q+8] |= tableSet[r+8];
					else
						dataIn[q+8] &= PAL_CLR[r+8];
				}

			}

			incrementer++;
			if (incrementer == 8)
			{
				q += incrementer;
				incrementer = 0;
			}

		}

// Put the new data back in. If no data was new, it still gets put back in.
		for(int a = firstTileOffset; a < smallerThanFile; a++)
		{
			inFile.put(dataIn[a]);
		}

// Close the file
		inFile.close();

// Let the user know if there was a color conversion or not
		if (gotOne == 1)
		{
			cout << "\n    Palette color " << argv[4] << " has been changed to palette color " << argv[5] << endl;
			cout << "     on tiles " << argv[2] << " through " << argv[3] << "." << endl;
			cout << "\n    Conversion complete!" << endl;
		}
		else
		{
			cout << "\n    Palette color " << argv[4] << " not found in tiles " << argv[2] << " through " << argv[3] << "." << endl;
			cout << "    No conversion has taken place." << endl;
			cout << "    " << ENDING << endl;
		}

	}
	return 0;
}
