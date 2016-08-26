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
#include <windows.h>
#include <string>
#include <mmsystem.h>

#define numOfAis 2


double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool rendmapbool = false;
short randRendmap1 = 0;//store the first maze type number
short randRendmap2 = 0;//store the second maze type number
short randRendmap3 = 0;//store the third maze type number
char MazeMap[40][80];
double timer = 0;
double gameTime = 60;//Set time 1min
double gameScore = 0; //Set starting score
double addScore = 1;//Set score per sec

char Name[40][80];

COORD b;

//Positions
short randPointX;
short randPointY;

short randPointX2;
short randPointY2;

short AIpositionX = 1;
short AIpositionY = 25;

short AIpositionX2 = 50;
short AIpositionY2 = 2;

bool checkloca = false;

std::string line;
std::fstream myfile;

//AIs
SGameBots gameAIs[numOfAis];
double AItime = 0.0;


// Game specific variables here
SGameChar   g_sChar;
SGameChar   g_sChar2;

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
EGAMESTATES g_eGameState2 = S_GAME;

bool bSomethingHappened = false;
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
void init(void)
{

	// Set precision for floating point output
	g_dElapsedTime = 0.0;
	g_dBounceTime = 0.0;

	// sets the initial state for the game
	g_eGameState = S_SPLASHSCREEN;

	g_sChar.m_cLocation.X = 1;
	g_sChar.m_cLocation.Y = 2;
	g_sChar.m_bActive = true;

	g_sChar2.m_cLocation.X = 50;//g_Console.getConsoleSize().X / 3;
	g_sChar2.m_cLocation.Y = 25;//g_Console.getConsoleSize().Y / 4;
	g_sChar2.m_bActive = true;
	// sets the width, height and the font name to use in the console
	g_Console.setConsoleFont(0, 16, L"Consolas");

	//AIs==========================
	Aiinit();

	storeMazeMap();
	openLogo();
	sound();
	readAnimation();
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown(void)
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
void getInput(void)
{
	g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
	g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
	g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	g_abKeyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
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
	case S_SPLASHSCREEN: splashScreenWait(); // game logic for the splash screen
		break;
	case S_SELECT: selectionScreen();
		break;
	case S_GAME: gameplay(); // gameplay logic when we are in the game
		break;
	case S_GAMEOVER: gameOver();
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
	case S_SELECT: renderSelectionScreen();
		break;
	case S_GAME: renderGame();
		break;
	case S_GAMEOVER:  renderGameOver();
		break;

	}
	renderFramerate();  // renders debug information, frame rate, elapsed time, etc
	renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 2.0) // wait for 3 seconds to switch to game mode, else do nothing
		g_eGameState = S_SELECT;
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

	if (g_dBounceTime > g_dElapsedTime)
		return;

	// Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_UP])
		characterMovement(B_UP);//2
	if (g_abKeyPressed[K_DOWN])
		characterMovement(B_DOWN);//3
	if (g_abKeyPressed[K_LEFT])
		characterMovement(B_LEFT);//0
	if (g_abKeyPressed[K_RIGHT])
		characterMovement(B_RIGHT);//1

	/*if (g_abKeyPressed[K_SPACE])
	{
		g_sChar.m_bActive = !g_sChar.m_bActive;
		g_sChar2.m_bActive = !g_sChar2.m_bActive;
		bSomethingHappened = true;
	}*/

	//when both character touches
	if (g_sChar.m_cLocation.X == g_sChar2.m_cLocation.X && g_sChar.m_cLocation.Y == g_sChar2.m_cLocation.Y)
	{

		rendmapbool = false;

		storeMazeMap();

		while (checkloca)
		{
			randPointX = (rand() % 25) + 1;
			randPointY = (rand() % 18) + 2;

			randPointX2 = (rand() % 20) + 2;
			randPointY2 = (rand() % 25) + 1;

			if (MazeMap[randPointY][randPointX] != 'M' && MazeMap[randPointY][randPointX] != '#'
				&& MazeMap[randPointY2][randPointX2] != 'M' && MazeMap[randPointY2][randPointX2] != '#')
			{

				checkloca = false;
			}
		}

		g_sChar.m_cLocation.X = randPointX;
		g_sChar.m_cLocation.Y = randPointY;

		g_sChar2.m_cLocation.X = randPointX2;
		g_sChar2.m_cLocation.Y = randPointY2;

		Aiinit();

		gameTime = 60;
		addScore++;
	}

	if (bSomethingHappened)
	{
		// set the bounce time to some time in the future to prevent accidental triggers
		g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enougInfant Annihilatorh
	}

	for (int i = 0; i < numOfAis; ++i)
	{
		if (gameAIs[i].m_cLocation.X == g_sChar.m_cLocation.X && gameAIs[i].m_cLocation.Y == g_sChar.m_cLocation.Y
			|| gameAIs[i].m_cLocation.X == g_sChar2.m_cLocation.X && gameAIs[i].m_cLocation.Y == g_sChar2.m_cLocation.Y)
		{
			g_eGameState = S_GAMEOVER;
		}
		
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
	g_Console.clearBuffer(0x09);
}


void renderGame()
{

	renderMap(); // renders the map to the buffer first
	renderAI();
	renderCharacter();  // renders the character into the buffer
	renderTime();
	score();
	
}

void renderMap()
{
	COORD c;

	for (int bRow = 1; bRow < 27; bRow++)
	{
		for (int bCol = 0; bCol < 52; bCol++)
		{
			char pix;
			pix = MazeMap[bRow][bCol];
			c.X = bCol;
			c.Y = bRow;

			if (MazeMap[bRow][bCol] == 'M')
			{
				g_Console.writeToBuffer(c, pix, 0xFF);
			}
			else if (MazeMap[bRow][bCol] == '#')
			{
				g_Console.writeToBuffer(c, pix, 0x22);
			}
			else
			{
				g_Console.writeToBuffer(c, pix, 0x09);
			}
		}
	}
}
void renderCharacter()
{
	// Draw the location of the character
	WORD charColor = 0x0C;
	WORD charColor2 = 0x0C;

	if (g_sChar.m_bActive)
	{
		charColor = 0x0B;
	}
	if (g_sChar2.m_bActive)
	{
		charColor2 = 0x0D;
	}
	g_Console.writeToBuffer(g_sChar.m_cLocation, 0x95, charColor);
	g_Console.writeToBuffer(g_sChar2.m_cLocation, 0x94, charColor2);
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

void renderAI()
{
	WORD AIColor = 0x9F;
	WORD AIColorPathFind = 0xCF;

	for (int i = 0; i < numOfAis; ++i)
	{
		if (gameAIs[i].m_bActive == true)
			g_Console.writeToBuffer(gameAIs[i].m_cLocation, (char)2, AIColor);
		else
			g_Console.writeToBuffer(gameAIs[i].m_cLocation, (char)2, AIColorPathFind);
	}
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


	for (int i = 0; i < numOfAis; ++i)
	{
		AiViewRange(&gameAIs[i]);					//Check if there is any Char in the view range. If there is, PathfindToChar will be set to true
		if (gameAIs[i].PathfindToChar == false)		//If there is no Pathfinding
		{
			BotRoam(&gameAIs[i]);					//Let the Ai Roam around
			AiPresenceArea(&gameAIs[i]);			//Check if the Ai exits the Roam area. If true, get them back to their respective areas
			gameAIs[i].m_bActive = true;
		}

		else if (gameAIs[i].PathfindToChar == true)	//If there is Pathfinding
		{
			gameAIs[i].m_bActive = false;			//Changes colour
			AIPathFind(&gameAIs[i], gameAIs[i].PathfindCoord.X, gameAIs[i].PathfindCoord.Y); //Pathfinds to coordinate

			if (gameAIs[i].m_cLocation.X == gameAIs[i].PathfindCoord.X && gameAIs[i].m_cLocation.Y == gameAIs[i].PathfindCoord.Y)
				gameAIs[i].PathfindToChar = false;	//If Ai reaches Coordinates, set to false and continue roaming in another frame

			AiPresenceArea(&gameAIs[i]);			//Checks and ensures Ai stays in roam area.
		}
	}

	//This Allows the Ai to roam and have a view range of 10m in a cone radius of about 52degrees
	//If Char enters the view range, the Ai will store the coordinates of the last seen of Char and pathfind to that location
	//If Char exits the viewrange when pathfinding is active, Ai will still go to the last seen location and roam

	//End of void moveAI
}

void sound()
{
	//sound
	PlaySound(TEXT("The Sense Of Me by Mud Flow.wav"), NULL, SND_ASYNC | SND_LOOP);

}