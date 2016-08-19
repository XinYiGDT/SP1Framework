#include "randMazeTypes.h"
#include "Framework\console.h"
#include <fstream>

extern Console g_Console;

void randMazeTypes(int maze, int row)
{
	COORD mazeC;
	std::string line;
	std::fstream myfile;
	//std::string line;
	//std::fstream myfile;

	switch (maze)
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
			mazeC.X = 1;
			mazeC.Y = row;
			row++;
			g_Console.writeToBuffer(mazeC, line, 0x05);
		}
		myfile.close();
	}

}