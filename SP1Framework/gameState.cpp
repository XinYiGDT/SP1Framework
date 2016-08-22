#include "gameState.h"
#include "Framework\console.h"
#include <string>

using namespace std;

extern EGAMESTATES g_eGameState;
extern bool bSomethingHappened;
extern bool g_abKeyPressed[K_COUNT];
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern Console g_Console;

int pressed = 0;


void selectionScreen()
{
	string Menu[3] = { "Play Game", "Mini Puzzle Game", "Exit game" };
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;

	switch (pressed)
	{
	case 0:
		g_Console.writeToBuffer(c, Menu[0], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x09);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x09);
		break;
	case 1:
		g_Console.writeToBuffer(c, Menu[0], 0x09);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x03);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x09);
		break;
	case 2:
		g_Console.writeToBuffer(c, Menu[0], 0x09);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[1], 0x09);
		c.Y += 1;
		g_Console.writeToBuffer(c, Menu[2], 0x03);
		break;
	default:
		if (pressed < 0)
		{
			pressed = 2;
		}
		else if (pressed > 2)
		{
			pressed = 0;
		}
		break;
	}

	if (g_dBounceTime > g_dElapsedTime)
	{
		return;
	}

	bSomethingHappened = false;
	
	if (g_abKeyPressed[K_UP])
	{
		pressed--;
		bSomethingHappened = true;
	}
	if (g_abKeyPressed[K_DOWN])
	{
		pressed++;
		bSomethingHappened = true;
	}
	
	if (g_abKeyPressed[K_ENTER])
	{
		if (pressed == 0)
		{
			g_eGameState = S_GAME;
		}
		else if (pressed == 1)
		{

		}
		else
		{
			g_bQuitGame = true;
		}

	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.325; // 125ms should be enougInfant Annihilatorh
	}
}

void gameOver()
{

}