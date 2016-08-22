#include "storeMazeMap.h"
#include "Framework\console.h"
#include <fstream>
#include <string>
#include <iomanip>

extern char MazeMap[40][80];
extern short randRendmap1;
extern short randRendmap2;
extern short randRendmap3;
extern bool rendmapbool;
extern Console g_Console;

//extern short colX;
//extern short rowY;
short colX = 1;
short rowY = 2;

extern bool checkloca;

extern std::string line;
extern std::fstream myfile;

void storeMazeMap()
{
	colX = 1;//reset this variable
	rowY = 2;

	int bRow = 1;
	int bCol = 0;

	myfile.open("border.txt");

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{

			for (int i = 0; i < 52; i++)
			{
				if (line[i] == 'M')
				{
					MazeMap[bRow][i] = 'M';
				}
				else
				{
					MazeMap[bRow][i] = ' ';
				}
			}

			bRow++;
		}
		myfile.close();
	}



	for (int i = 0; i < 3; i++)
	{
		short randMap = 0;

		srand(time(NULL) + i);

		if (!rendmapbool)
		{
			randMap = rand() % 9;
			if (i == 0)
			{
				randRendmap1 = randMap;
				mazeCoords(randRendmap1, 1);
			}
			else if (i == 1)
			{
				randRendmap2 = randMap;
				mazeCoords(randRendmap2, 2);
			}
			else if (i == 2)
			{
				randRendmap3 = randMap;
				mazeCoords(randRendmap3, 3);
			}

			if (i == 2)
			{
				rendmapbool = true;
				checkloca = true;
			}
		}

	}
}

void mazeCoords(int mazetype, int mazenumber)
{

	if (mazenumber == 1)
	{
		openMazeType(mazetype);
	}
	else if (mazenumber == 2)
	{
		openMazeType(mazetype);
	}
	else if (mazenumber == 3)
	{
		openMazeType(mazetype);
	}

}
void openMazeType(short mazeNum)
{
	switch (mazeNum)
	{
	case 0: myfile.open("map1.txt");
		break;
	case 1: myfile.open("map2.txt");
		break;
	case 2: myfile.open("map3.txt");
		break;
	case 3: myfile.open("map4.txt");
		break;
	case 4: myfile.open("map5.txt");
		break;
	case 5: myfile.open("map6.txt");
		break;
	case 6: myfile.open("map7.txt");
		break;
	case 7: myfile.open("map8.txt");
		break;
	case 8: myfile.open("map9.txt");
		break;
	}

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			for (int i = 0; i < 50; i++)
			{
				if (line[i] == '#')
				{
					MazeMap[rowY][colX] = '#';
					colX++;
				}
				else
				{
					MazeMap[rowY][colX] = ' ';
					colX++;
				}
			}
			colX = 1;
			rowY++;
		}
		myfile.close();
	}
}