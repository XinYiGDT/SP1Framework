#include "gametimer.h"
#include "Framework\console.h"
extern double gameTime;
extern double timer;
extern double g_dElapsedTime;
extern Console g_Console;

void renderTime()
{
	COORD timercoord;
	COORD timecoordA;
	COORD timecoordB;

	std::string timerstr = "Time Left: ";
	timercoord.X = 52 / 2 - (timerstr.length() / 2) - 1;
	timercoord.Y = 27;
	timecoordA.X = 52 / 2 + (timerstr.length() / 2) + 1;
	timecoordA.Y = 27;
	timecoordB.X = 52 / 2 + (timerstr.length() / 2) + 2;
	timecoordB.Y = 27;

	char A, B;
	int gTime = gameTime;
	B = gTime % 10 + 48;
	A = gTime / 10 + 48;

	if (timer == 0)
	{
		timer = g_dElapsedTime;
	}
	else
	{
		if (g_dElapsedTime - timer > 1)
		{
			timer = 0;
		}
		g_Console.writeToBuffer(timercoord, timerstr);
		g_Console.writeToBuffer(timecoordA, A);
		g_Console.writeToBuffer(timecoordB, B);
		return;
	}

	gameTime--;


	g_Console.writeToBuffer(timercoord, timerstr);
	g_Console.writeToBuffer(timecoordA, A);
	g_Console.writeToBuffer(timecoordB, B);



}
