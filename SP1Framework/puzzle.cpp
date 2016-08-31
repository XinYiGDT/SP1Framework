#include "puzzle.h"
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Framework\console.h"
#include <sstream>
#include <cmath>

using namespace std;
double moveSpeedTime = 0;
extern double g_dElapsedTime;
char SnakeMap[40][80];
extern Console g_Console;
bool gameOver1 = false;
//bool cont;
const int width = 49;
const int height = 25;
int x, y, fruitX, fruitY;
//int tailX[100], tailY[100];
int nTail = 0;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct SnakeTail
{
	COORD Child;
	COORD Parent;
	int TDirection;
};
SnakeTail Tail[100];

extern EGAMESTATES g_eGameState;


eDirecton dir;
extern std::string line;
extern std::fstream myfile;
COORD ins;
bool unset = true;//check if random-ed
bool scont = false;
COORD s;
COORD f;
int sscore = 0;
int targetScore = 0;

void Setup()//This initialises only once when the game starts.
{
	gameOver1 = false;
	scont = false;
	x = width / 2;
	y = height / 2;
	fruitX = width - 1;
	fruitY = height - 1;

	moveSpeedTime = 0;
	sscore = 0;
	targetScore = 0;
	nTail = 0;



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
					SnakeMap[bRow][i] = 'M';
				}
				else
				{
					SnakeMap[bRow][i] = ' ';
				}
			}

			bRow++;
		}
		myfile.close();
	}

	Tail[0].Child.X = 5;
	Tail[0].Child.Y = 5;

	
	Tail[100];

}
void rendersnake()
{


	COORD c;

	for (int bRow = 1; bRow < 27; bRow++)
	{
		for (int bCol = 0; bCol < 52; bCol++)
		{
			char pix;
			pix = SnakeMap[bRow][bCol];
			c.X = bCol;
			c.Y = bRow;

			if (SnakeMap[bRow][bCol] == 'M')
			{
				g_Console.writeToBuffer(c, pix, 0xFF);
			}
			else
			{
				g_Console.writeToBuffer(c, pix, 0x09);
			}
		}
	}

	ins.X = 0;
	ins.Y = 28;
	g_Console.writeToBuffer(ins, "W to move up");
	ins.X = 0;
	ins.Y = 29;
	g_Console.writeToBuffer(ins, "A to move left");
	ins.X = 0;
	ins.Y = 30;
	g_Console.writeToBuffer(ins, "S to move down");
	ins.X = 0;
	ins.Y = 31;
	g_Console.writeToBuffer(ins, "D to move right");
	ins.X = 0;
	ins.Y = 32;
	std::string sscorestr = std::to_string(sscore);
	g_Console.writeToBuffer(ins, "Score : " + sscorestr);
	if (gameOver1 == true)
	{
		g_eGameState = S_GAMEOVER;
	}
	if (scont == true)
	{
		g_eGameState = S_GAME;

		unset = true;//check if random-ed
		dir = STOP;
		scont = false;
	}

	if (unset)//if not yet random
	{
		s.Y = rand() % y + 2;
		s.X = rand() % x + 1;
		f.Y = rand() % fruitY + 3;
		if (f.Y == 0 || f.Y >= 25)
		{
			f.Y = rand() % fruitY + 3;
		}
		f.X = rand() % fruitX + 2;
		if (f.X == 0 || f.X >= 50)
		{
			f.X = rand() % fruitX + 2;
		}
		unset = false;

		targetScore = sscore + 30;
	}


	


	
	for (int i = 0; i <= nTail; i++)
	{
		COORD body;
		body.X = Tail[i].Child.X;
		body.Y = Tail[i].Child.Y;

		g_Console.writeToBuffer(body, "o");
	}


	g_Console.writeToBuffer(f, "F");

}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (dir != RIGHT)
				dir = LEFT;
			break;
		case 'd':
			if (dir != LEFT)
				dir = RIGHT;
			break;
		case 'w':
			if (dir != DOWN)
				dir = UP;
			break;
		case 's':
			if (dir != UP)
				dir = DOWN;
			break;
		case 'x':
			gameOver1 = true;
			break;
		}
	}
}
void snakelogic()
{
	
	Input();


	if (moveSpeedTime == 0)
	{
		moveSpeedTime = g_dElapsedTime;
	}
	else
	{
		if (g_dElapsedTime - moveSpeedTime > 0.075)
			moveSpeedTime = 0;
		return;
	}

	

	switch (dir)
	{
	case LEFT:
		Tail[0].Child.X--;
		Tail[0].TDirection = LEFT;//register new direction
		break;
	case RIGHT:
		Tail[0].Child.X++;
		Tail[0].TDirection = RIGHT;
		break;
	case UP:
		Tail[0].Child.Y--;
		Tail[0].TDirection = UP;
		break;
	case DOWN:
		Tail[0].Child.Y++;
		Tail[0].TDirection = DOWN;
		break;
	default:
		break;
	}

	for (int i = 1; i <= nTail; i++)
	{
		//Ensure that the spawn of the next node is smooth
		if (Tail[i].Child.X - Tail[i].Parent.X == 1)//eg 3(current) - 2(next) == 1. snake is going left
		{
			Tail[i].TDirection = LEFT;
		}
		else if (Tail[i].Child.X - Tail[i].Parent.X == 1)//eg 2(current) - 3(next) == -1. snake is going right
		{
			Tail[i].TDirection = RIGHT;
		}
		else if (Tail[i].Child.Y - Tail[i].Parent.Y == 1)//eg 3(current) - 2(next) == 1. snake is going up
		{
			Tail[i].TDirection = UP;
		}
		else  if (Tail[i].Child.Y - Tail[i].Parent.Y == -1)//eg 2(current) - 3(next) == -1. snake is going down
		{
			Tail[i].TDirection = DOWN;
		}
		Tail[i].Child.X = Tail[i].Parent.X;//move to the next location
		Tail[i].Child.Y = Tail[i].Parent.Y;

		Tail[i].Parent.X = Tail[i - 1].Child.X;
		Tail[i].Parent.Y = Tail[i - 1].Child.Y;


	}



	for (int i = 1; i <= nTail; i++)
	{
		if (Tail[0].Child.X == Tail[i].Child.X && Tail[0].Child.Y == Tail[i].Child.Y && dir != STOP)//Check if head collides with any of the tail nodes. if true, gameover.
		{
			gameOver1 = true;
			break;
		}
	}
	if (Tail[0].Child.X > width || Tail[0].Child.X < 1 || Tail[0].Child.Y > height || Tail[0].Child.Y < 2)
	{
		gameOver1 = true;
	}
	if (sscore >= targetScore)
	{
		scont = true;
	}



	if (Tail[0].Child.X == f.X && Tail[0].Child.Y == f.Y)
	{

		nTail++;


		if (Tail[nTail - 1].TDirection == LEFT)
		{
			//Tail[nTail - 1].TDirection = DOWN;
			Tail[nTail].Child.X = Tail[nTail -1].Child.X + 1;//If head moved left and hit fruit, tail would be on the right side.
			Tail[nTail].Child.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].Parent.X = Tail[nTail - 1].Child.X;//assign parent
			Tail[nTail].Parent.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].TDirection = LEFT;
		}
		else if (Tail[nTail - 1].TDirection == RIGHT)
		{
			Tail[nTail].Child.X = Tail[nTail - 1].Child.X - 1;//If head moved right and hit fruit, tail would be on the left side.
			Tail[nTail].Child.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].Parent.X = Tail[nTail - 1].Child.X;
			Tail[nTail].Parent.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].TDirection = RIGHT;
		}
		else if (Tail[nTail - 1].TDirection == UP)
		{
			Tail[nTail].Child.X = Tail[nTail - 1].Child.X;//If head moved up and hit fruit, tail would be below.
			Tail[nTail].Child.Y = Tail[nTail - 1].Child.Y + 1;

			Tail[nTail].Parent.X = Tail[nTail - 1].Child.X;
			Tail[nTail].Parent.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].TDirection = UP;
		}
		else if (Tail[nTail - 1].TDirection == DOWN)
		{
			Tail[nTail].Child.X = Tail[nTail - 1].Child.X;//If head moved down and hit fruit, tail would be above.
			Tail[nTail].Child.Y = Tail[nTail - 1].Child.Y - 1;

			Tail[nTail].Parent.X = Tail[nTail - 1].Child.X;//assign next node of new node as parent
			Tail[nTail].Parent.Y = Tail[nTail - 1].Child.Y;

			Tail[nTail].TDirection = DOWN;
		}


		//Random fruit spawn location
		do
		{
			f.Y = rand() % fruitY + 3;
		} while (f.Y == 0 || f.Y >= 24);

		do
		{
			f.X = rand() % fruitX + 2;
		} while (f.X == 0 || f.X >= 47);


		sscore += 10;
		
	}

}

