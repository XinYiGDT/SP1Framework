#include "Pup.h"
#include "Framework\console.h"

extern Console g_Console;
extern double gameTime;
extern SGameChar g_sChar;
extern SGameChar g_sChar2;
extern SGamePup g_sPup;
extern char MazeMap[40][80];
extern bool checkloca;

void Pup()
{


	short PuprandPointX;
	short PuprandPointY;

	if (g_sChar.m_cLocation.X == g_sPup.m_cLocation.X && g_sChar.m_cLocation.Y == g_sPup.m_cLocation.Y ||
		g_sChar2.m_cLocation.X == g_sPup.m_cLocation.X && g_sChar2.m_cLocation.Y == g_sPup.m_cLocation.Y) //check collision
	{
		gameTime += 10;
		g_sPup.m_bActive = false;
	}

	if (g_sPup.m_bActive == false)
	{
		while (true)
		{
			PuprandPointX = rand() % 50 + 1;
			PuprandPointY = rand() % 24 + 2;
			if (MazeMap[PuprandPointY][PuprandPointX] != 'M' && MazeMap[PuprandPointY][PuprandPointX] != '#')
			{
				g_sPup.m_cLocation.X = PuprandPointX;
				g_sPup.m_cLocation.Y = PuprandPointY;
				break;
			}
		}

		g_sPup.m_bActive = true;
	}
	g_Console.writeToBuffer(g_sPup.m_cLocation, "@");
}