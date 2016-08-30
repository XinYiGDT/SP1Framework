#include "AIPathFind.h"
#include <iomanip>


bool unsetDir = true;
extern char MazeMap[40][80];
short x = 1;

void BotRoam(struct SGameBots *Ai)
{
	srand(time(NULL));
	bool haveWall = false;

	//Increase chances to change in direction when there are walls nearby. The nearer the wall, the more chance to change in direction
	for (int y = -2; y < 3; ++y)
	{
		for (int x = -2; x < 3; ++x)
		{
			if ((x == -2 || y == -2 || x == 2 || y == 2) && (MazeMap[y][x] == 'M' || MazeMap[y][x] == (char)219))
				x++;

			if (1 <= x && x <= 1 && 1 <= y && y <= 1 && (MazeMap[y][x] == 'M' || MazeMap[y][x] == (char)219))
				x += 2;
		}
	}

	//Random sudden change of direction
	short ChanceToChangeDirection = 0;
	ChanceToChangeDirection = rand() % 15;
	if (0 <= ChanceToChangeDirection && ChanceToChangeDirection < x)//Chances to sudden change of direction increase every fail attempt
	{
		haveWall = true;
		x = 1;
	}
	else
		x++;

	if (unsetDir)
	{
		short randomDir = rand() % 4;
		switch (randomDir)
		{
		case 0: Ai->g_bDirection = B_LEFT;
			break;
		case 1: Ai->g_bDirection = B_RIGHT;
			break;
		case 2: Ai->g_bDirection = B_UP;
			break;
		case 3: Ai->g_bDirection = B_DOWN;
			break;
		}
		unsetDir = false;
	}

	if (Ai->g_bDirection == B_LEFT)
	{
		//Check if next location is obstructed. If not, move to that location.
		if (!(MazeMap[Ai->m_cLocation.Y][Ai->m_cLocation.X - 1] == 'M' || MazeMap[Ai->m_cLocation.Y][Ai->m_cLocation.X - 1] == (char)219))
			Ai->m_cLocation.X--;
		else
			haveWall = true;
	}
	if (Ai->g_bDirection == B_RIGHT)
	{
		//Check if next location is obstructed. If not, move to that location.
		if (!(MazeMap[Ai->m_cLocation.Y][Ai->m_cLocation.X + 1] == 'M' || MazeMap[Ai->m_cLocation.Y][Ai->m_cLocation.X + 1] == (char)219))
			Ai->m_cLocation.X++;
		else
			haveWall = true;
	}
	if (Ai->g_bDirection == B_UP)
	{
		//Check if next location is obstructed. If not, move to that location.
		if (!(MazeMap[Ai->m_cLocation.Y - 1][Ai->m_cLocation.X] == 'M' || MazeMap[Ai->m_cLocation.Y - 1][Ai->m_cLocation.X] == (char)219))
			Ai->m_cLocation.Y--;
		else
			haveWall = true;
	}
	if (Ai->g_bDirection == B_DOWN)
	{
		//Check if next location is obstructed. If not, move to that location.
		if (!(MazeMap[Ai->m_cLocation.Y + 1][Ai->m_cLocation.X] == 'M' || MazeMap[Ai->m_cLocation.Y + 1][Ai->m_cLocation.X] == (char)219))
			Ai->m_cLocation.Y++;
		else
			haveWall = true;
	}

	if (haveWall)
	{
		short ignoreThisDir = Ai->g_bDirection;
		short randDir = 0;
		do
		{
			randDir = rand() % 4;
			if (ignoreThisDir != randDir)
			{
				if ((randDir == 0 || randDir == 2 && randDir != ignoreThisDir + 1)//Dont allow Bots to turn back on collision on first direction finding
					|| (randDir == 1 || randDir == 3 && randDir != ignoreThisDir - 1))
				{
					switch (randDir)
					{
					case 0: Ai->g_bDirection = B_LEFT;
						break;
					case 1: Ai->g_bDirection = B_RIGHT;
						break;
					case 2: Ai->g_bDirection = B_UP;
						break;
					case 3: Ai->g_bDirection = B_DOWN;
						break;
					}
				}
			}

		} while (ignoreThisDir == randDir);//repeat if it is the same direction
	}

}