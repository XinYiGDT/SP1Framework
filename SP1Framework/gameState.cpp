#include "gameState.h"
#include "Framework\console.h"
#include <fstream>
#include <string>

using namespace std;

extern EGAMESTATES g_eGameState;
extern bool bSomethingHappened;
extern bool g_abKeyPressed[K_COUNT];
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern Console g_Console;

string line2;
extern fstream myfile;

extern char Name[40][80];
int nRow = 1;

int pressed = 0;

void openLogo()
{
	myfile.open("name3.txt");

	//reading
	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{

			for (int i = 0; i < 70; i++)
			{
				if (line2[i] == '>')
				{
					Name[nRow][i] = '>';
				}
				else if (line2[i] == '<')
				{
					Name[nRow][i] = '<';
				}
				else
				{
					Name[nRow][i] = ' ';
				}
			}

			nRow++;
		}
		myfile.close();
	}
}

void renderSplashScreen()  // renders the splash screen
{
	COORD c = g_Console.getConsoleSize();
	c.Y /= 3;
	c.X = c.X / 2 - 9;
	g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 20;
	g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
	c.Y += 1;
	c.X = g_Console.getConsoleSize().X / 2 - 9;
	g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);


}

void renderSelectionScreen()
{
	string Menu[3] = { "Play Game", "Mini Puzzle Game", "Exit game" };
	COORD c = g_Console.getConsoleSize();
	COORD b = g_Console.getConsoleSize();;
	c.Y /= 3;
	c.X = c.X / 2 - 9;

	//Printing it
	for (int bRow = 1; bRow < 9; bRow++)
	{
		for (int bCol = 0; bCol < 70; bCol++)
		{
			char pix;
			pix = Name[bRow][bCol];
			b.X = bCol;
			b.Y = bRow;

			if (Name[bRow][bCol] != ' ')
			{
				g_Console.writeToBuffer(b, pix, 0xF3);
			}
			else
			{
				g_Console.writeToBuffer(b, pix, 0x88);
			}
		}
	}

	g_Console.writeToBuffer(c, Menu[0], (pressed == 0 ? 0x03 : 0x09));
	c.Y += 1;
	g_Console.writeToBuffer(c, Menu[1], (pressed == 1 ? 0x03 : 0x09));
	c.Y += 1;
	g_Console.writeToBuffer(c, Menu[2], (pressed == 2 ? 0x03 : 0x09));


}

void selectionScreen()
{

	if (pressed < 0)
	{
		pressed = 2;
	}
	else if (pressed > 2)
	{
		pressed = 0;
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
		g_dBounceTime = g_dElapsedTime + 0.325; // 125ms should be enough
	}
}

void gameOver()
{

}