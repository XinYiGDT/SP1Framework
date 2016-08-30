#include "AIPathFind.h"

extern SGameBots gameAIs[];

void Aiinit()
{
	gameAIs[0].m_cLocation.X = 1;
	gameAIs[0].m_cLocation.Y = 25;
	gameAIs[0].g_bRoamAreaA.X = 0;
	gameAIs[0].g_bRoamAreaA.Y = 13;
	gameAIs[0].g_bRoamAreaB.X = 25;
	gameAIs[0].g_bRoamAreaB.Y = 26;
	gameAIs[0].m_bActive = true;
	gameAIs[0].PathfindToChar = false;

	gameAIs[1].m_cLocation.X = 50;
	gameAIs[1].m_cLocation.Y = 2;
	gameAIs[1].g_bRoamAreaA.X = 25;
	gameAIs[1].g_bRoamAreaA.Y = 1;
	gameAIs[1].g_bRoamAreaB.X = 52;
	gameAIs[1].g_bRoamAreaB.Y = 13;
	gameAIs[1].m_bActive = true;
	gameAIs[1].PathfindToChar = false;

	gameAIs[2].m_cLocation.X = 25;
	gameAIs[2].m_cLocation.Y = 13;
	gameAIs[2].g_bRoamAreaA.X = 10;
	gameAIs[2].g_bRoamAreaA.Y = 5;
	gameAIs[2].g_bRoamAreaB.X = 40;
	gameAIs[2].g_bRoamAreaB.Y = 21;
	gameAIs[2].m_bActive = true;
	gameAIs[2].PathfindToChar = false;

}