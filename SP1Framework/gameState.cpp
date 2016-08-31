#include "gameState.h"
#include "Framework\console.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

extern EGAMESTATES g_eGameState;
extern bool bSomethingHappened;
extern bool g_abKeyPressed[K_COUNT];
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern Console g_Console;
extern double gameScore;
bool GOentered = false;
int highscore[5] = { 0, };
bool storedHs = false;

string line2;
extern fstream myfile;

extern char Name[40][80];
extern char text[50][80];
extern char go[40][80];
int nRow = 1;

int pressed = 0;

int up = 0;

int animationOffset;
double resetTime;
double animationOffset2 = 0.0;

COORD e = g_Console.getConsoleSize();
int bRow = 1;
int bCol = 0;

bool moveup = true;

void openFiles()
{
	myfile.open("name.txt");

	//reading logo
	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{

			for (int i = 0; i < 75; i++)
			{
				if (line2[i] == '#')
				{
					Name[nRow][i] = '#';
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
	nRow = 0;

	myfile.open("Credit.txt");

	//reading credit text
	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{

			for (int i = 0; i < 75; i++)
			{
				if (line2[i] == '#')
				{
					text[nRow][i] = (char)219;
				}
				else if (line2[i] == '\0')
				{
					break;
				}
				else
				{
					text[nRow][i] = ' ';
				}
			}

			nRow++;
		}
		myfile.close();
	}

	nRow = 0;
	myfile.open("GameOver.txt");

	//read Gameover text
	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{

			for (int i = 0; i < 75; i++)
			{
				if (line2[i] == '\0')
				{
					break;
				}
				else
				{
					go[nRow][i] = line2[i];
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
	string loadingstr = "Now Loading...";
	c.Y /= 3;
	c.X = c.X / 2 - loadingstr.length()/2;
	g_Console.writeToBuffer(c, loadingstr, 0x0D);
}

void renderSelectionScreen()
{
	string Menu[5] = { "Play Game", "Instructions", "Mini Puzzle Game", "Credits" , "Exit game" };
	COORD c = g_Console.getConsoleSize();
	COORD b = g_Console.getConsoleSize();
	c.Y /= 2;
	c.X = c.X / 2 - 9;

	//Printing logo
	for (int bRow = 1; bRow < 8; bRow++)
	{
		for (int bCol = 0; bCol < 75; bCol++)
		{
			char pix;
			pix = Name[bRow][bCol];
			b.X = bCol + 3;
			b.Y = bRow + 5;

			if (Name[bRow][bCol] != ' ')
			{
				g_Console.writeToBuffer(b, pix, 0xFF);
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
	c.Y += 1;
	g_Console.writeToBuffer(c, Menu[3], (pressed == 3 ? 0x03 : 0x09));
	c.Y += 1;
	g_Console.writeToBuffer(c, Menu[4], (pressed == 4 ? 0x03 : 0x09));

	COORD x;
	x.X = 5;
	x.Y = 20;

	if (animationOffset == 0)
	{
		animationOffset = g_dElapsedTime;
	}

	if (g_dElapsedTime - animationOffset < 0.4 )
	{
		renderAnimation(0, x);
	}
	else if (g_dElapsedTime + animationOffset > 0.3)
	{
		renderAnimation(1, x);
		animationOffset = 0.3;
	}

	x.X = 55;
	x.Y = 20;

	if (g_dElapsedTime - animationOffset < 0.4)
	{
		renderAnimation(2, x);
	}
	else if (g_dElapsedTime + animationOffset > 0.3)
	{
		renderAnimation(3, x);
		animationOffset = 0.3;
	}
	
}

void selectionScreen()
{

	if (pressed < 0)
	{
		pressed = 4;
	}
	else if (pressed > 4)
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
			g_eGameState = S_INSTRUCTIONS;
		}
		else if (pressed == 2)
		{
			g_eGameState = S_MGAME_TETRIS;
		}
		else if (pressed == 3)
		{
			g_eGameState = S_CREDIT;
		}
		else
		{
			g_bQuitGame = true;
		}

	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.3; // 125ms should be enough
	}
}

extern bool rendmapbool;
extern bool checkloca;
vector<int> something;
void gameOver()
{
	ofstream hsfile; //write file
	ifstream hsReadFile; //read file

	if (GOentered == false)//Enter once only
	{
		double tempscore;
		hsfile.open("highscore.txt", ios::app);
	
		
		hsfile << gameScore << endl;
		hsReadFile.open("highscore.txt");
		while (true) //loop to read each line
		{	
			hsReadFile >> line2;

			if (hsReadFile.eof())
				break;

			

			something.push_back(stoi(line2)); //put each score into vector

		
		
		}
		hsfile.close();
		hsReadFile.close();
		GOentered = true;
	}

	if (storedHs == false)
	{
		hsReadFile.open("highscore.txt");
		if (hsReadFile.is_open())
		{
			for (int j = 0; j < 5; j++) //loop to get the highest 5 score
			{
				double tempscore = 0;
				for (int k = 0; k < something.size(); k++)
				{
					if (something[k] > tempscore)//if X score in the allscores array is larger than the tempscore
					{
						bool insidehs = false;
						for (int l = 0; l < 5; l++)
						{
							if (highscore[l] == something[k]) //check if all score is alr inside highscore
							{
								insidehs = true;
							}

						}
						if (insidehs == false)//if the score is NOT inside the highscore array, assign that score to tempscore
						{
							tempscore = something[k];
						}
					}
				}
				highscore[j] = tempscore;
			}
			hsReadFile.close();
		}

		storedHs = true;
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		init();
		rendmapbool = false;
		checkloca = false;
		renderMap();
		g_eGameState = S_SELECT;
		
	}
}

void renderGameOver()
{
	COORD d = g_Console.getConsoleSize();

	for (int bRow = 0; bRow < 9; bRow++)
	{
		for (int bCol = 0; bCol < 75; bCol++)
		{
			char pix;
			pix = go[bRow][bCol];
			d.X = bCol + 12;
			d.Y = bRow + 10;

			if (go[bRow][bCol] != ' ')
			{
				g_Console.writeToBuffer(d, pix, 0x0F);
			}
			else
			{
				g_Console.writeToBuffer(d, pix, 0x08);
			}
		}
	}


	string hsstr = "HIGHSCORE";
	g_Console.writeToBuffer(g_Console.getConsoleSize().X / 2 - hsstr.length()/2, g_Console.getConsoleSize().Y / 2 - 1, hsstr);
	COORD hscoord;
	hscoord.Y = g_Console.getConsoleSize().Y / 2;
	for (int i = 0; i < 5; i++)
	{
		string highscorestr = to_string(highscore[i]);

		hscoord.X = g_Console.getConsoleSize().X / 2 - highscorestr.length() / 2;

		g_Console.writeToBuffer(hscoord, highscorestr);
		hscoord.Y++;
	}



	string escGOstr = "Press Esc to exit to main menu";
	g_Console.writeToBuffer(g_Console.getConsoleSize().X / 2 - escGOstr.length() / 2, hscoord.Y + 3, escGOstr);
}


void renderCredit()
{
	//printing the text
	if (moveup==true)
	{
		e.X = 0 + 15;
		e.Y = 1 + 33;

		moveup = false;
	}
	for (bRow = 1; bRow < 50; bRow++)
	{
		for (bCol = 0; bCol < 75; bCol++)
		{
			char pix;
			pix = text[bRow][bCol];
			
			

			if (text[bRow][bCol] != ' ')
			{
				g_Console.writeToBuffer(e.X + bCol, e.Y + bRow, pix, 0x08);
			}
			else
			{
				g_Console.writeToBuffer(e.X + bCol, e.Y + bRow, pix, 0x0D);
			}
		}
	}

	//animation
	/*if (animationOffset == 0)
	{
		animationOffset = g_dElapsedTime;
	}*/

	if (g_dElapsedTime - animationOffset2 > 0.07)
	{
		e.Y--;
		animationOffset2 = g_dElapsedTime;
	}
	else
	{
		return;
	}
	
	
}

void credit()
{

	if (g_dElapsedTime - resetTime > 10.0) // wait for 10 seconds to switch to game mode, else do nothing
	{
		g_eGameState = S_SELECT;
		resetTime = g_dElapsedTime;

		if (moveup == false)
		{
			moveup = true;
		}
	}
	else
	{
		return;
	}
}