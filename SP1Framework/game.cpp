// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>
#include <string>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool rendmapbool = false;
short randRendmap1 = 0;//store the first maze type number
short randRendmap2 = 0;//store the second maze type number
short randRendmap3 = 0;//store the third maze type number
char Frame[40][52];
double timer = 0;
double gameTime = 60;//Set time 1min

COORD b;
short rowX = 1;
short colY = 2;

short randPointX;
short randPointY;

short randPointX2;
short randPointY2;

char Wall1[80][40];//holds coordinates of first maze type	32 is space, -37 is Û.	Holds coords Y = 0 to Y = 9
char Wall2[80][40];//holds coordinates of second maze type							Holds coords Y = 10 to Y = 17
char Wall3[80][40];//holds coordinates of third maze type							Holds coords Y = 18 to Y = 25

std::string line;
std::fstream myfile;




//AIs
SGameChar g_sAI;	//AIs
SGameChar g_sAI2;
double AItime = 0.0;

// Game specific variables here
SGameChar   g_sChar;
SGameChar   g_sChar2;

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMESTATES g_eGameState2 = S_GAME;

double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once 

// Console object
Console g_Console(80, 40, "SP1 Framework");

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;

	g_sChar2.m_cLocation.X = 20;//g_Console.getConsoleSize().X / 3;
	g_sChar2.m_cLocation.Y = 5;//g_Console.getConsoleSize().Y / 4;
	g_sChar2.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

	g_sAI.m_cLocation.X = 1;
	g_sAI.m_cLocation.Y = 2;
	g_sAI.m_bActive = true;

	g_sAI2.m_cLocation.X = 50;
	g_sAI2.m_cLocation.Y = 2;
	g_sAI2.m_bActive = true;

	
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: renderSplashScreen();
            break;
        case S_GAME: renderGame();
            break;

    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void gameplay()            // gameplay logic
{
	moveAI();
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.

}

void moveCharacter()
{
	
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_UP])
	{
		g_sChar2.m_cLocation.Y--;
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;

		//Border
		if (Frame[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M')
		{
			g_sChar.m_cLocation.Y++;
		}
		if (Frame[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M')
		{
			g_sChar2.m_cLocation.Y++;
		}

		//Wall
		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y++;
			}
		}

	if (g_sChar2.m_cLocation.Y >= 0 && g_sChar2.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 10 && g_sChar2.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 18 && g_sChar2.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
	}
	if (g_abKeyPressed[K_DOWN])
	{
		g_sChar.m_cLocation.Y++;
		g_sChar2.m_cLocation.Y++;
		bSomethingHappened = true;

		//Border
		if (Frame[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M')
		{
			g_sChar.m_cLocation.Y--;
		}
		if (Frame[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M')
		{
			g_sChar2.m_cLocation.Y--;
		}

		//Wall
		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}

		if (g_sChar2.m_cLocation.Y >= 0 && g_sChar2.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y--;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 10 && g_sChar2.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y--;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 18 && g_sChar2.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y--;
			}
		}
	}
	if (g_abKeyPressed[K_LEFT])
	{
		g_sChar.m_cLocation.X--;
		g_sChar2.m_cLocation.X--;
		bSomethingHappened = true;

		//Border
		if (Frame[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M')
		{
			g_sChar.m_cLocation.X++;
		}
		if (Frame[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M')
		{
			g_sChar2.m_cLocation.X++;
		}

		//Wall
		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}

		if (g_sChar2.m_cLocation.Y >= 0 && g_sChar2.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 10 && g_sChar2.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 18 && g_sChar2.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X++;
			}
		}
	}
	if (g_abKeyPressed[K_RIGHT])
	{
		g_sChar.m_cLocation.X++;
		g_sChar2.m_cLocation.X++;
		bSomethingHappened = true;

		//Border
		if (Frame[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M')
		{
			g_sChar.m_cLocation.X--;
		}
		if (Frame[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M')
		{
			g_sChar2.m_cLocation.X--;
		}

		//Wall
		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X--;
			}
		}

		if (g_sChar2.m_cLocation.Y >= 0 && g_sChar2.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X--;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 10 && g_sChar2.m_cLocation.Y < 18)
		{
			if (Wall2[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X--;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 18 && g_sChar2.m_cLocation.Y <= 25)
		{
			if (Wall3[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.X--;
			}
		}
	}

    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
		g_sChar2.m_bActive = !g_sChar2.m_bActive;
        bSomethingHappened = true;
    }

	if (g_sChar.m_cLocation.X == g_sChar2.m_cLocation.X && g_sChar.m_cLocation.Y == g_sChar2.m_cLocation.Y)
	{

		rendmapbool = false;

		for (int i = 0; i < 4; i++)
		{
			srand(time(NULL) + i);

			if (i == 0)
			{
				randPointX = (rand() % 25) + 1;
			}
			if (i == 1)
			{
				randPointY = (rand() % 14) + 2;
			}
			if (i == 2)
			{
				randPointX2 = (rand() % 25) + 24;
			}
			if (i == 3)
			{
				randPointY2 = (rand() % 14) + 13;
			}

		}

		g_sChar.m_cLocation.X = randPointX;
		g_sChar.m_cLocation.Y = randPointY;

		g_sChar2.m_cLocation.X = randPointX2;
		g_sChar2.m_cLocation.Y = randPointY2;

		rowX = 1;
		colY = 2;

		gameTime = 60;
	}

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
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

void renderGame()
{
	
	renderMap(); // renders the map to the buffer first
	renderAI();
    renderCharacter();  // renders the character into the buffer
	renderTime();
}

void renderMap()
{
	COORD c;
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
					Frame[bRow][i] = 'M';
				}
				else
				{
					Frame[bRow][i] = ' ';
				}
				
			}
			
			c.X = 0;
			c.Y = bRow;
			
			g_Console.writeToBuffer(c, line, 0x07);
			bRow++;
		}
		myfile.close();
	}

	

	for (int i = 0; i < 3; i++)
	{
		short randMap = 0;

		srand(time(NULL)+i);

		if (!rendmapbool)
		{
			randMap = rand() % 9;
			if (i == 0)
			{
				randRendmap1 = randMap;
				randMazeTypes(randRendmap1, 2);
				mazeCoords(randRendmap1, 1);
			}
			else if (i == 1)
			{
				randRendmap2 = randMap;
				randMazeTypes(randRendmap2, 10);
				mazeCoords(randRendmap2, 2);
			}
			else if (i == 2)
			{
				randRendmap3 = randMap;
				randMazeTypes(randRendmap3, 18);
				mazeCoords(randRendmap3, 3);
			}

			if (i == 2) rendmapbool = true;
		}
		else
		{
			if (i == 0)
			{
				randMazeTypes(randRendmap1, 2);
			}
			else if (i == 1)
			{
				randMazeTypes(randRendmap2, 10);
			}
			else if (i == 2)
			{
				randMazeTypes(randRendmap3, 18);
			}

		}

	}

	
}
void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
	if (g_sChar.m_bActive && g_sChar2.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
	g_Console.writeToBuffer(g_sChar2.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void storeGlobalWall(char *map, int mazenumber)
{


	for (short i = 0; colY < 2 + (8* mazenumber); i++)
	{
		if (i % 50 == 0 && i !=0)
		{
			rowX = 1;
			colY++;
		}
		if (mazenumber == 1)
		{
			Wall1[rowX][colY] = map[i];
		}
		else if (mazenumber == 2)
		{
			Wall2[rowX][colY] = map[i];
		}
		else if (mazenumber == 3)
		{
			Wall3[rowX][colY] = map[i];
		}
		if (colY != 2 + (8 * mazenumber))
		{
			rowX++;
		}
	}

}

void renderAI()
{
	WORD AIColor = 0xFF;
	if (g_sAI.m_bActive)
	{
		AIColor = 0xCF;
	}
	g_Console.writeToBuffer(g_sAI.m_cLocation, (char)2, AIColor);
	g_Console.writeToBuffer(g_sAI2.m_cLocation, (char)2, AIColor);
}


void moveAI()
{

	if (AItime == 0)
		AItime = g_dElapsedTime;
	else
	{
		if (g_dElapsedTime - AItime > 0.5)
			AItime = 0;
		return;
	}

	AIPathFind(&g_sAI);
	AIPathFind(&g_sAI2);
//End of void moveAI
}

