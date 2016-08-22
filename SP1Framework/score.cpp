#include "score.h"
#include "Framework\console.h"

extern double addScore;
extern double gameScore;
double scoretimer = 0;
extern double g_dElapsedTime;
extern Console g_Console;

 void score()
{
	COORD scorecoord;
	COORD scorecoordA;

	std::string scorestr = "Score: ";
	scorecoord.X = 52 / 2 - (scorestr.length() / 2);
	scorecoord.Y = 28;
	scorecoordA.X = 52 / 2 + (scorestr.length() / 2) + 1;
	scorecoordA.Y = 28;

	int gScore = gameScore;
	std::string stringScore = std::to_string(gScore);
	if (scoretimer == 0)
	{
		scoretimer = g_dElapsedTime;
	}
	else
	{
		if (g_dElapsedTime - scoretimer > 1)
		{
			scoretimer = 0;
		}

		g_Console.writeToBuffer(scorecoord, scorestr);
		g_Console.writeToBuffer(scorecoordA, stringScore);
		return;
	}
	gameScore += addScore;
	

	g_Console.writeToBuffer(scorecoord, scorestr);
	g_Console.writeToBuffer(scorecoordA, stringScore);
}