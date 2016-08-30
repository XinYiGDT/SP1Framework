#include "TetrisMinigame.h"
#include "Framework\console.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <string>
#include <queue>
#include <utility>

//Border Walls
char TetrisWalls[40][80];
int WallWidth = 0; //15 including walls

//Timing
extern double g_dBounceTime;
extern double g_dElapsedTime;
double Tettime;
extern double Tetdelay;

extern bool g_abKeyPressed[K_COUNT];

//Shapes
char TetShapes[7][4][5][5];
char TetShapesInGame[40][80];

bool newShape;//=false
int RandShapeNumber = 0;
int RandShapeRotation = 0;
bool reachedBottom;//=false

struct DataOfFallingShape
{
	int RandomShapeNumber;
	int RandomShapeRotation;
	COORD fallingShapeCoords[4];
};

struct ShapeCoords
{
	COORD PivotCoord;
	COORD RotatingCoord1;
	COORD RotatingCoord2;
	COORD RotatingCoord3;
};
ShapeCoords newShapeC;
DataOfFallingShape FallingShape;
DataOfFallingShape HoldShapeData;
bool FirstHoldShape;

//Queue shapes
int QueuedShapes[3][2];
int randomQShape = 0;//just for random seeding


bool TetloseGame;//=false

extern Console g_Console;

extern std::string line;
extern std::fstream myfile;

int Tetscore;

int containerStart = (g_Console.getConsoleSize().X / 2) - 6;//(g_Console.getConsoleSize().X / 2) - (WallWidth / 2) + 1
int containerEnd = (g_Console.getConsoleSize().X / 2) + 6;//(g_Console.getConsoleSize().X / 2) + (WallWidth / 2) - 1

extern EGAMESTATES g_eGameState;


int a;
int b;
bool settest = false;
void tetris()
{
	TetShapes[7][4][5][5] = { 0, };
	for (int row = 0; row < 40; row++)//Force reset
	{
		for (int col = 0; col < 80; col++)
		{
			TetShapesInGame[row][col] = '\0';
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			QueuedShapes[i][j] = 'x';
		}
	}
	tetinit();
	TetloseGame = false;
	newShape = true;
	reachedBottom = false;
	Tetscore = 0;
	AddtoQueue();

	//initialise holdshape data
	for (int i = 0; i > 4; i++)
	{
		HoldShapeData.fallingShapeCoords[i].X = 99;
		HoldShapeData.fallingShapeCoords[i].Y = 99;
	}
	HoldShapeData.RandomShapeNumber = 99;
	HoldShapeData.RandomShapeRotation = 99;

	FirstHoldShape = false;
}
void tetrisUpdate()
{
	//AddtoQueue();
	loadNewShape();
	moveShape();
	gravity();
	checkRows();

}
void rendertetris()
{

	COORD TetWall;

	for (int TRow = 1; TRow < 27; TRow++)
	{
		TetWall.X = 0;//Consolesize - half of the Wall size
		TetWall.Y = TRow;
		for (int i = 0; i < 80; i++)
		{

			char pix = TetrisWalls[TRow][i];
			g_Console.writeToBuffer(TetWall, pix);
			TetWall.X++;

		}
	}

	COORD renderholdShapeborder;
	renderholdShapeborder.X = g_Console.getConsoleSize().X / 2 - WallWidth / 2 - 9;
	renderholdShapeborder.Y = 4;

	for (int m = 0; m < 7; m++)
	{
		for (int n = 0; n < 7; n++)
		{
			g_Console.writeToBuffer(renderholdShapeborder.X + n, renderholdShapeborder.Y + m, 'M', 0xFF);
		}
	}
	std::string holdshapeinst1 = "Press 'C'";
	std::string holdshapeinst2 = "to Hold Shape";
	g_Console.writeToBuffer(renderholdShapeborder.X - 2, 11, holdshapeinst1);
	g_Console.writeToBuffer(renderholdShapeborder.X - 5, 12, holdshapeinst2);

	COORD renderholdShape;
	renderholdShape.X = g_Console.getConsoleSize().X / 2 - WallWidth / 2 - 8;
	renderholdShape.Y = 5;

	for (int j = 0; j < 5; j++)
	{
		for (int k = 0; k < 5; k++)
		{
			HoldShapeData.RandomShapeNumber;
			HoldShapeData.RandomShapeRotation;
			if (HoldShapeData.RandomShapeNumber != 99 && HoldShapeData.RandomShapeRotation != 99)
			{
				char p = TetShapes[HoldShapeData.RandomShapeNumber][HoldShapeData.RandomShapeRotation][j][k];
				g_Console.writeToBuffer(renderholdShape.X + k, renderholdShape.Y + j, p);
			}
			else
			{
				g_Console.writeToBuffer(renderholdShape.X + k, renderholdShape.Y + j, ' ');
			}
		}
	}



	COORD rendShape;

	for (int i = 0; i < 4; i++)
	{
		rendShape.X = FallingShape.fallingShapeCoords[i].X;
		rendShape.Y = FallingShape.fallingShapeCoords[i].Y;
		g_Console.writeToBuffer(rendShape, '#');
	}

	COORD fixedShape;
	for (int row = 0; row < 27; row++)
	{
		for (int col = 0; col < 80; col++)
		{
			if (TetShapesInGame[row][col] == '#')
			{
				fixedShape.X = col;
				fixedShape.Y = row;
				g_Console.writeToBuffer(fixedShape, '#');
			}

		}
	}

	COORD tetscorec;
	std::string tetscorestr = "Score: " + std::to_string(Tetscore);
	tetscorec.X = g_Console.getConsoleSize().X / 2 - tetscorestr.length() / 2;
	tetscorec.Y = 27;
	g_Console.writeToBuffer(tetscorec, tetscorestr);


	COORD rotationinstc;
	std::string rotationinststr = "Press 'z' to rotate";
	rotationinstc.X = g_Console.getConsoleSize().X / 2 - rotationinststr.length() / 2;
	rotationinstc.Y = tetscorec.Y + 1;
	g_Console.writeToBuffer(rotationinstc, rotationinststr);

	//QueueShapes Border===
	COORD renderQShapeborder;
	renderQShapeborder.X = g_Console.getConsoleSize().X / 2 + WallWidth / 2 + 3;
	renderQShapeborder.Y = 4;
	for (int m = 0; m <19; m++)
	{
		for (int n = 0; n < 7; n++)
		{
			g_Console.writeToBuffer(renderQShapeborder.X + m, renderQShapeborder.Y + n, 'M', 0xFF);
		}
	}
	g_Console.writeToBuffer(renderQShapeborder.X, 3, "Next Shape:");


	COORD renderQ1;
	COORD renderQ2;
	COORD renderQ3;
	renderQ1.X = g_Console.getConsoleSize().X / 2 + WallWidth / 2 + 4;
	renderQ1.Y = 5;
	renderQ2.X = g_Console.getConsoleSize().X / 2 + WallWidth / 2 + 10;
	renderQ2.Y = 5;
	renderQ3.X = g_Console.getConsoleSize().X / 2 + WallWidth / 2 + 16;
	renderQ3.Y = 5;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (i == 0)
				{
					char pixs = TetShapes[QueuedShapes[i][0]][QueuedShapes[i][1]][j][k];
					g_Console.writeToBuffer(renderQ1.X + k, renderQ1.Y + j, pixs);
				}
				else if (i == 1)
				{
					char pixs = TetShapes[QueuedShapes[i][0]][QueuedShapes[i][1]][j][k];
					g_Console.writeToBuffer(renderQ2.X + k, renderQ2.Y + j, pixs);
				}
				else if (i == 2)
				{
					char pixs = TetShapes[QueuedShapes[i][0]][QueuedShapes[i][1]][j][k];
					g_Console.writeToBuffer(renderQ3.X + k, renderQ3.Y + j, pixs);
				}
			}
		}
	}


	if (TetloseGame)
	{
		COORD tetEndScore;
		COORD losec;
		COORD Restartins;

		std::string loseStr = "You LOSE!";
		std::string endScorestr = "Your Score: " + std::to_string(Tetscore);
		std::string Restartinststr = "Press R to restart game";

		losec.X = g_Console.getConsoleSize().X / 2 - loseStr.length() / 2;
		losec.Y = g_Console.getConsoleSize().Y / 2 - 1;
		tetEndScore.X = g_Console.getConsoleSize().X / 2 - endScorestr.length() / 2;
		tetEndScore.Y = g_Console.getConsoleSize().Y / 2;
		Restartins.X = g_Console.getConsoleSize().X / 2 - Restartinststr.length() / 2;
		Restartins.Y = g_Console.getConsoleSize().Y / 2 + 1;

		g_Console.writeToBuffer(losec, loseStr, 0xCF);
		g_Console.writeToBuffer(tetEndScore, endScorestr);
		g_Console.writeToBuffer(Restartins, Restartinststr, 0xF0);

		if (g_abKeyPressed[K_R])
		{
			clearScreen();
			tetris();
			TetloseGame = false;
		}
	}
}

void checkRows()
{
	bool rollFall = false;//Trigger this when there is a line that is suppose to fall
	for (int SRow = 30; SRow > 0; SRow--)
	{
		bool RowComplete = true;
		for (int SCol = containerStart; SCol <= containerEnd; SCol++)
		{
			if (TetShapesInGame[SRow][SCol] != '#')
			{
				RowComplete = false;
			}
		}

		if (rollFall)//let all the rolls above to drop
		{
			for (int SCol = containerStart; SCol <= containerEnd; SCol++)
			{
				if (TetShapesInGame[SRow][SCol] == '#')
				{
					TetShapesInGame[SRow][SCol] = '\0';
					TetShapesInGame[SRow + 1][SCol] = '#';
				}
			}
		}

		if (RowComplete)
		{
			for (int SCol = containerStart; SCol <= containerEnd; SCol++)
			{
				TetShapesInGame[SRow][SCol] = '\0';
			}
			rollFall = true;
			Tetscore += 100;
		}

	}


	for (int SCol = containerStart; SCol <= containerEnd; SCol++)
	{
		if (TetShapesInGame[1][SCol] == '#')
		{
			TetloseGame = true;
		}
	}
}

void AddtoQueue()
{

	for (int i = 0; i < 3; i++)
	{
		if (QueuedShapes[i][0] == 'x' && QueuedShapes[i][1] == 'x')//'x' == 120
		{
			srand(time(NULL) + randomQShape);
			RandShapeNumber = (rand() % 7);

			srand(time(NULL) + RandShapeNumber + randomQShape);
			RandShapeRotation = (rand() % 4);

			QueuedShapes[i][0] = RandShapeNumber;
			QueuedShapes[i][1] = RandShapeRotation;

			randomQShape++;
		}
	}

}

void loadNewShape()
{
	if (newShape == true && TetloseGame == false)
	{
		newShape = false;

		ShapeCoords newShapeC;
		int shapecoordcount = 0;
		for (int SRow = 0; SRow < 5; SRow++)
		{
			for (int SCol = 0; SCol < 5; SCol++)
			{

				char pix = TetShapes[QueuedShapes[0][0]][QueuedShapes[0][1]][SRow][SCol];
				if (pix == '#')
				{
					if (shapecoordcount == 0)
					{
						newShapeC.RotatingCoord1.X = SCol - 2;
						newShapeC.RotatingCoord1.Y = SRow - 2;
						shapecoordcount++;
					}
					else if (shapecoordcount == 1)
					{
						newShapeC.RotatingCoord2.X = SCol - 2;
						newShapeC.RotatingCoord2.Y = SRow - 2;
						shapecoordcount++;
					}
					else if (shapecoordcount == 2)
					{
						newShapeC.RotatingCoord3.X = SCol - 2;
						newShapeC.RotatingCoord3.Y = SRow - 2;

					}
				}
				if (pix == '!')
				{
					newShapeC.PivotCoord.X = SCol - 2;
					newShapeC.PivotCoord.Y = SRow - 2;

				}
			}
		}
		if (FirstHoldShape == false)
		{
			//This step spawns the new shape in the container
			FallingShape.fallingShapeCoords[1].X = newShapeC.RotatingCoord1.X + g_Console.getConsoleSize().X / 2;
			FallingShape.fallingShapeCoords[1].Y = newShapeC.RotatingCoord1.Y;

			FallingShape.fallingShapeCoords[2].X = newShapeC.RotatingCoord2.X + g_Console.getConsoleSize().X / 2;
			FallingShape.fallingShapeCoords[2].Y = newShapeC.RotatingCoord2.Y;

			FallingShape.fallingShapeCoords[3].X = newShapeC.RotatingCoord3.X + g_Console.getConsoleSize().X / 2;
			FallingShape.fallingShapeCoords[3].Y = newShapeC.RotatingCoord3.Y;

			FallingShape.fallingShapeCoords[0].X = newShapeC.PivotCoord.X + g_Console.getConsoleSize().X / 2;
			FallingShape.fallingShapeCoords[0].Y = newShapeC.PivotCoord.Y;
		}
		else
		{
			FallingShape.fallingShapeCoords[1].X = newShapeC.RotatingCoord1.X + FallingShape.fallingShapeCoords[0].X;
			FallingShape.fallingShapeCoords[1].Y = newShapeC.RotatingCoord1.Y + FallingShape.fallingShapeCoords[0].Y;

			FallingShape.fallingShapeCoords[2].X = newShapeC.RotatingCoord2.X + FallingShape.fallingShapeCoords[0].X;
			FallingShape.fallingShapeCoords[2].Y = newShapeC.RotatingCoord2.Y + FallingShape.fallingShapeCoords[0].Y;

			FallingShape.fallingShapeCoords[3].X = newShapeC.RotatingCoord3.X + FallingShape.fallingShapeCoords[0].X;
			FallingShape.fallingShapeCoords[3].Y = newShapeC.RotatingCoord3.Y + FallingShape.fallingShapeCoords[0].Y;

			FallingShape.fallingShapeCoords[0].X = newShapeC.PivotCoord.X + FallingShape.fallingShapeCoords[0].X;
			FallingShape.fallingShapeCoords[0].Y = newShapeC.PivotCoord.Y + FallingShape.fallingShapeCoords[0].Y;
			FirstHoldShape = false;

		}
		FallingShape.RandomShapeNumber = QueuedShapes[0][0];
		FallingShape.RandomShapeRotation = QueuedShapes[0][1];

		//As new shape is used to spawn,
		//This will push the queue forward and empties the last slot
		for (int i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				continue;
			}
			QueuedShapes[i - 1][0] = QueuedShapes[i][0];
			QueuedShapes[i - 1][1] = QueuedShapes[i][1];
			if (i == 2)
			{
				QueuedShapes[i][0] = 'x';
				QueuedShapes[i][1] = 'x';
			}
		}

		AddtoQueue();//Add one more shape into queue after popping one shape

	}



}

void holdShape()
{

	if (HoldShapeData.RandomShapeNumber == 99)
	{
		HoldShapeData.RandomShapeNumber = FallingShape.RandomShapeNumber;
		HoldShapeData.RandomShapeRotation = FallingShape.RandomShapeRotation;

		newShape = true;
		FirstHoldShape = true;
		return;
	}
	int tempRSN;
	int tempRSR;

	tempRSN = HoldShapeData.RandomShapeNumber;
	tempRSR = HoldShapeData.RandomShapeRotation;

	HoldShapeData.RandomShapeNumber = FallingShape.RandomShapeNumber;
	HoldShapeData.RandomShapeRotation = FallingShape.RandomShapeRotation;

	FallingShape.RandomShapeNumber = tempRSN;
	FallingShape.RandomShapeRotation = tempRSR;


	//This step finds the coordinates of all points in relative to the pivot
	int shapecoordcount = 0;
	for (int SRow = 0; SRow < 5; SRow++)
	{
		for (int SCol = 0; SCol < 5; SCol++)
		{

			char pix = TetShapes[FallingShape.RandomShapeNumber][FallingShape.RandomShapeRotation][SRow][SCol];
			if (pix == '#')
			{
				if (shapecoordcount == 0)
				{
					HoldShapeData.fallingShapeCoords[1].X = SCol - 2;
					HoldShapeData.fallingShapeCoords[1].Y = SRow - 2;
					shapecoordcount++;
				}
				else if (shapecoordcount == 1)
				{
					HoldShapeData.fallingShapeCoords[2].X = SCol - 2;
					HoldShapeData.fallingShapeCoords[2].Y = SRow - 2;
					shapecoordcount++;
				}
				else if (shapecoordcount == 2)
				{
					HoldShapeData.fallingShapeCoords[3].X = SCol - 2;
					HoldShapeData.fallingShapeCoords[3].Y = SRow - 2;
				}
			}
			if (pix == '!')
			{
				HoldShapeData.fallingShapeCoords[0].X = SCol - 2;
				HoldShapeData.fallingShapeCoords[0].Y = SRow - 2;

			}
		}
	}

	//fallingShapeCoords[0] is the pivoting point
	FallingShape.fallingShapeCoords[0].X = FallingShape.fallingShapeCoords[0].X + HoldShapeData.fallingShapeCoords[0].X;
	FallingShape.fallingShapeCoords[0].Y = FallingShape.fallingShapeCoords[0].Y + HoldShapeData.fallingShapeCoords[0].Y;

	//HoldShapeData.fallingShapeCoords[i].X / .Y is the coordinates relative to the pivot
	//FallingShape.fallingShapeCoords[0].X / .Y + HoldShapeData.fallingShapeCoords[i].X / .Y will find the coordinate of a point
	FallingShape.fallingShapeCoords[1].X = FallingShape.fallingShapeCoords[0].X + HoldShapeData.fallingShapeCoords[1].X;
	FallingShape.fallingShapeCoords[1].Y = FallingShape.fallingShapeCoords[0].Y + HoldShapeData.fallingShapeCoords[1].Y;

	FallingShape.fallingShapeCoords[2].X = FallingShape.fallingShapeCoords[0].X + HoldShapeData.fallingShapeCoords[2].X;
	FallingShape.fallingShapeCoords[2].Y = FallingShape.fallingShapeCoords[0].Y + HoldShapeData.fallingShapeCoords[2].Y;

	FallingShape.fallingShapeCoords[3].X = FallingShape.fallingShapeCoords[0].X + HoldShapeData.fallingShapeCoords[3].X;
	FallingShape.fallingShapeCoords[3].Y = FallingShape.fallingShapeCoords[0].Y + HoldShapeData.fallingShapeCoords[3].Y;

}