#include "TetrisMinigame.h"



//Border
extern char TetrisWalls[40][80];

//Timing
extern double g_dBounceTime;
extern double g_dElapsedTime;
extern double Tetdelay;

//Shapes
extern char TetShapesInGame[40][80];

extern struct DataOfFallingShape
{
	int RandomShapeNumber;
	int RandomShapeRotation;
	COORD fallingShapeCoords[4];
};

extern DataOfFallingShape FallingShape;

//extern COORD newShapeCoords[4];
extern struct ShapeCoords
{
	COORD PivotCoord;
	COORD RotatingCoord1;
	COORD RotatingCoord2;
	COORD RotatingCoord3;
};
extern ShapeCoords newShapeC;

extern bool g_abKeyPressed[K_COUNT];


void moveShape()
{

	bool TSomethingHappened = false;
	bool TRotateSomethingHappened = false;
	if (g_abKeyPressed[K_LEFT])
	{
		bool gotOneCoordTouch = false;
		for (int i = 0; i < 4; i++)
		{
			if (TetShapesInGame[FallingShape.fallingShapeCoords[i].Y][FallingShape.fallingShapeCoords[i].X - 1] == '#'
				|| TetrisWalls[FallingShape.fallingShapeCoords[i].Y][(FallingShape.fallingShapeCoords[i].X - 1)] == 'M')
			{
				TSomethingHappened = true;
				gotOneCoordTouch = true;
				break;
			}
		}
		if (gotOneCoordTouch == false)
		{
			if (g_dBounceTime > g_dElapsedTime)
				return;
			for (int i = 0; i < 4; i++)
			{
				FallingShape.fallingShapeCoords[i].X--;
				TSomethingHappened = true;
			}
		}
	}
	if (g_abKeyPressed[K_RIGHT])
	{
		bool gotOneCoordTouch = false;
		for (int i = 0; i < 4; i++)
		{
			if (TetShapesInGame[FallingShape.fallingShapeCoords[i].Y][FallingShape.fallingShapeCoords[i].X + 1] == '#'
				|| TetrisWalls[FallingShape.fallingShapeCoords[i].Y][FallingShape.fallingShapeCoords[i].X + 1] == 'M')
			{
				TSomethingHappened = true;
				gotOneCoordTouch = true;
				break;
			}
		}
		if (gotOneCoordTouch == false)
		{
			if (g_dBounceTime > g_dElapsedTime)
				return;
			for (int i = 0; i < 4; i++)
			{
				FallingShape.fallingShapeCoords[i].X++;
				TSomethingHappened = true;
			}
		}
	}

	if (g_abKeyPressed[K_Z])
	{
		bool gotOneCoordTouch = false;
		for (int i = 1; i < 4; i++)//newShapeCoord[0] is the pivot. This do not need to be checked if rotation will collide
		{
			int RotatedX = 0;
			int RotatedY = 0;
			if (i == 1)
			{
				RotatedX = FallingShape.fallingShapeCoords[i].Y - FallingShape.fallingShapeCoords[0].Y;//newShapeC.RotatingCoord1.Y;//Rotation matrix
				RotatedY = -1 * (FallingShape.fallingShapeCoords[i].X - FallingShape.fallingShapeCoords[0].X);
			}
			else if (i == 2)
			{
				RotatedX = FallingShape.fallingShapeCoords[i].Y - FallingShape.fallingShapeCoords[0].Y;//Rotation matrix
				RotatedY = -1 * (FallingShape.fallingShapeCoords[i].X - FallingShape.fallingShapeCoords[0].X);
			}
			else if (i == 3)
			{
				RotatedX = FallingShape.fallingShapeCoords[i].Y - FallingShape.fallingShapeCoords[0].Y;//Rotation matrix
				RotatedY = -1 * (FallingShape.fallingShapeCoords[i].X - FallingShape.fallingShapeCoords[0].X);
			}
			RotatedX = FallingShape.fallingShapeCoords[0].X + RotatedX;
			RotatedY = FallingShape.fallingShapeCoords[0].Y + RotatedY;
			if (TetShapesInGame[RotatedY][RotatedX] == '#'
				|| TetrisWalls[RotatedY][RotatedX] == 'M')
			{
				TSomethingHappened = true;
				gotOneCoordTouch = true;
				break;
			}
		}
		if (gotOneCoordTouch == false)
		{
			if (g_dBounceTime > g_dElapsedTime)
				return;
			TRotateSomethingHappened = true;

			int RX = 0;
			int RY = 0;

			newShapeC.PivotCoord.X;
			newShapeC.PivotCoord.Y;
			// Rotation Matrix [ 0  1 ]
			//                 [ -1 0 ]
			RX = FallingShape.fallingShapeCoords[1].Y - FallingShape.fallingShapeCoords[0].Y;//Rotation matrix
			RY = -1 * (FallingShape.fallingShapeCoords[1].X - FallingShape.fallingShapeCoords[0].X);
			//			newShapeC.RotatingCoord1.X = RX;
			//			newShapeC.RotatingCoord1.Y = RY;
			FallingShape.fallingShapeCoords[1].X = FallingShape.fallingShapeCoords[0].X + RX;// newShapeC.RotatingCoord1.X;
			FallingShape.fallingShapeCoords[1].Y = FallingShape.fallingShapeCoords[0].Y + RY;// newShapeC.RotatingCoord1.Y;

			RX = FallingShape.fallingShapeCoords[2].Y - FallingShape.fallingShapeCoords[0].Y;//Rotation matrix
			RY = -1 * (FallingShape.fallingShapeCoords[2].X - FallingShape.fallingShapeCoords[0].X);
			//			newShapeC.RotatingCoord1.X = RX;
			//			newShapeC.RotatingCoord1.Y = RY;
			FallingShape.fallingShapeCoords[2].X = FallingShape.fallingShapeCoords[0].X + RX;// newShapeC.RotatingCoord2.X;
			FallingShape.fallingShapeCoords[2].Y = FallingShape.fallingShapeCoords[0].Y + RY;// newShapeC.RotatingCoord2.Y;

			RX = FallingShape.fallingShapeCoords[3].Y - FallingShape.fallingShapeCoords[0].Y;//Rotation matrix
			RY = -1 * (FallingShape.fallingShapeCoords[3].X - FallingShape.fallingShapeCoords[0].X);
			//			newShapeC.RotatingCoord1.X = RX;
			//			newShapeC.RotatingCoord1.Y = RY;
			FallingShape.fallingShapeCoords[3].X = FallingShape.fallingShapeCoords[0].X + RX;// newShapeC.RotatingCoord3.X;
			FallingShape.fallingShapeCoords[3].Y = FallingShape.fallingShapeCoords[0].Y + RY;// newShapeC.RotatingCoord3.Y;		}
		}

	}

	if (g_abKeyPressed[K_C])
	{
		if (g_dBounceTime > g_dElapsedTime)
			return;
		holdShape();

		TRotateSomethingHappened = true;
	}

	if (g_abKeyPressed[K_SPACE])
	{
		Tetdelay = 0.05;
	}
	else
	{
		Tetdelay = 0.5;
	}

	if (TSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.100; // 125ms should be enough
	}
	if (TRotateSomethingHappened)
	{
		g_dBounceTime = g_dElapsedTime + 0.250;
	}
}