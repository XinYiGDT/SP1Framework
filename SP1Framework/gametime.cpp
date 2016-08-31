#include "gametimer.h"
#include "Framework\console.h"
extern int gameTime;
extern double timer;
extern double g_dElapsedTime;
extern Console g_Console;

void renderTime()
{
	COORD timercoord;
	COORD timecoordA;
	COORD timecoordB;

	std::string timerstr = "Time Left: ";
	timerstr += std::to_string(gameTime);

	timercoord.X = 52 / 2 - (timerstr.length() / 2) - 1;
	timercoord.Y = 27;

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

		return;
	}

	gameTime--;


	g_Console.writeToBuffer(timercoord, timerstr);




}
