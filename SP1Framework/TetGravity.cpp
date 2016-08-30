#include "TetrisMinigame.h"
#include "Framework\console.h"

extern Console g_Console;
extern double Tettime;
extern double g_dElapsedTime;
double Tetdelay = 0.5;

extern bool reachedBottom;
extern struct DataOfFallingShape
{
	int RandomShapeNumber;
	int RandomShapeRotation;
	COORD fallingShapeCoords[4];
};

extern DataOfFallingShape FallingShape;
extern char TetShapesInGame[40][80];

extern int Tetscore;

extern bool newShape;

void gravity()
{

	for (int i = 0; i < 4; i++)
	{
		if (TetShapesInGame[FallingShape.fallingShapeCoords[i].Y + 1][FallingShape.fallingShapeCoords[i].X] == '#')//FallingShape.fallingShapeCoords[i].X
		{
			reachedBottom = true;
			newShape = true;
			break;

		}
		if (FallingShape.fallingShapeCoords[i].Y + 1 >= 26)//If any coords of falling shape reaches the end
		{
			reachedBottom = true;
			newShape = true;
		}
	}

	if (!reachedBottom)
	{

		if (g_dElapsedTime - Tettime > Tetdelay)
		{
			Tettime = g_dElapsedTime;
		}
		else
		{
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			FallingShape.fallingShapeCoords[i].Y++;
		}
		Tetscore++;
	}




	if (reachedBottom)//Store the coordinates when the falling shape lands.
	{
		for (int i = 0; i < 4; i++)
		{
			TetShapesInGame[FallingShape.fallingShapeCoords[i].Y][FallingShape.fallingShapeCoords[i].X] = '#';
		}
		reachedBottom = false;
	}

	/*
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	*/
}