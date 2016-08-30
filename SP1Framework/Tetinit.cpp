#include "TetrisMinigame.h"
#include "Framework\console.h"
#include <string>
#include <fstream>

extern Console g_Console;
extern std::string line;
extern std::fstream myfile;

extern char TetrisWalls[40][80];
extern int WallWidth;

extern char TetShapes[7][4][5][5];

void tetinit()
{
	short TcolX = 1;//reset this variable
	short TrowY = 2;

	int bRow = 1;
	int bCol = 0;

	myfile.open("border.txt");
	int icount = 0;
	if (myfile.is_open())
	{

		while (std::getline(myfile, line))
		{
			if (bRow == 1)
			{
				bRow++;
				continue;
			}
			for (int i = 0; i < 52; i++)
			{
				if (13 <= i && i <= 49)	//Recylcle the border.txt from MazeMap. 
				{						//This narrows the width
					icount++;
					continue;
				}
				if (line[i] == 'M')
				{
					TetrisWalls[bRow][i - icount + g_Console.getConsoleSize().X / 2 - 7] = 'M';//hardcode to store map in exact location
				}
				else
				{
					TetrisWalls[bRow][i - icount + g_Console.getConsoleSize().X / 2 - 7] = ' ';
				}
			}
			WallWidth = 52 - icount;
			icount = 0;
			bRow++;
		}
		myfile.close();
	}

	loadShapes();

}
void loadShapes()
{

	myfile.open("TetrisShapes.txt");
	if (myfile.is_open())
	{
		int sRow = 0;
		int shapeCount = 0;
		int Rotation = 0;
		while (std::getline(myfile, line))
		{

			if (line[0] == '=')//If line is the delimiter, skip
			{
				shapeCount++;
				sRow = 0;
				Rotation = 0;
				continue;
			}
			if (line[0] == '>')
			{
				Rotation++;
				sRow = 0;
				continue;
			}

			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == '#')
				{
					TetShapes[shapeCount][Rotation][sRow][i] = '#';
				}
				else if (line[i] == '-')
				{
					TetShapes[shapeCount][Rotation][sRow][i] = ' ';
				}
				else if (line[i] == '!')
				{
					TetShapes[shapeCount][Rotation][sRow][i] = '!';
				}
			}

			sRow++;

		}
		myfile.close();
	}

}