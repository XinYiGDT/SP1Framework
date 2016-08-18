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

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];
bool rendmapbool = false;
short randRendmap1 = 0;//store the first maze type number
short randRendmap2 = 0;//store the second maze type number
short randRendmap3 = 0;//store the third maze type number
char Frame[152][2];


COORD b;
short rowX = 1;
short colY = 2;


char Wall1[80][40];//holds coordinates of first maze type	32 is space, -37 is Û.	Holds coords Y = 0 to Y = 9
char Wall2[80][40];//holds coordinates of second maze type							Holds coords Y = 10 to Y = 17
char Wall3[80][40];//holds coordinates of third maze type							Holds coords Y = 18 to Y = 25

std::string line;
std::fstream myfile;




//AIs
SGameChar g_sAI;	//AIs
COORD AIPrevious;
double AItime = 0.0;

// Game specific variables here
SGameChar   g_sChar;
SGameChar   g_sChar2;

EGAMESTATES g_eGameState = S_SPLASHSCREEN;
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

	g_sAI.m_cLocation.X = g_Console.getConsoleSize().X / 5;
	g_sAI.m_cLocation.Y = g_Console.getConsoleSize().Y / 5;
	g_sAI.m_bActive = true;
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
	//border = isCollision(g_sChar, g_sChar2, Frame[152][2]);
	//isCollision(g_sChar, g_sChar2, Frame[152][2], g_abKeyPressed[K_COUNT]);
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character

	if (g_abKeyPressed[K_UP])
	{
		g_sChar2.m_cLocation.Y--;
		bSomethingHappened = true;

	if (g_sChar2.m_cLocation.Y >= 0 && g_sChar2.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 10 && g_sChar2.m_cLocation.Y < 18)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
		else if (g_sChar2.m_cLocation.Y >= 18 && g_sChar2.m_cLocation.Y <= 25)
		{
			if (Wall1[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '#')
			{
				g_sChar2.m_cLocation.Y++;
			}
		}
	}
	if (g_abKeyPressed[K_DOWN])
	{
		g_sChar2.m_cLocation.Y++;
		bSomethingHappened = true;

/*		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
			}
		}*/
	}
	if (g_abKeyPressed[K_LEFT])
	{
		g_sChar2.m_cLocation.X--;
		bSomethingHappened = true;

	/*	if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.X++;
			}
		}*/
	}
	if (g_abKeyPressed[K_RIGHT])
	{
		g_sChar2.m_cLocation.X++;
		g_sChar.m_cLocation.Y--;
		bSomethingHappened = true;

		if (g_sChar.m_cLocation.Y >= 0 && g_sChar.m_cLocation.Y < 10)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
				g_sChar.m_cLocation.Y++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 10 && g_sChar.m_cLocation.Y < 18)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
				g_sChar.m_cLocation.Y++;
			}
		}
		else if (g_sChar.m_cLocation.Y >= 18 && g_sChar.m_cLocation.Y <= 25)
		{
			if (Wall1[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '#')
			{
				g_sChar.m_cLocation.Y--;
				g_sChar.m_cLocation.Y++;
			}
		}
	}

	/*if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 2 && g_sChar2.m_cLocation.Y > 2)



	/*if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0 && g_sChar2.m_cLocation.Y > 0)
    {
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			g_sChar2.m_cLocation.Y--;
			bSomethingHappened = true;

			
    }
	else if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
	{
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;

			if (Frame[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y - 1] == '77')
			{
				g_sChar.m_cLocation.Y++;
			}

	}
	else if (g_abKeyPressed[K_UP] && g_sChar2.m_cLocation.Y > 0)
	{
		g_sChar2.m_cLocation.Y--;
		bSomethingHappened = true;

		if (Frame[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y - 1] == '77')
		{
			g_sChar2.m_cLocation.Y++;
		}

	}
	if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0 && g_sChar2.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
		g_sChar2.m_cLocation.X--;
        bSomethingHappened = true;

		
    }
	else if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
	{
		g_sChar.m_cLocation.X--;
		bSomethingHappened = true;

		if (Frame[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '77')
		{
			g_sChar.m_cLocation.X++;
		}
	}
	else if (g_abKeyPressed[K_LEFT] && g_sChar2.m_cLocation.X > 0)
	{
		g_sChar2.m_cLocation.X--;
		bSomethingHappened = true;

		if (Frame[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '77')
		{
			g_sChar2.m_cLocation.X++;
		}
	}
	if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1 && g_sChar2.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
		g_sChar.m_cLocation.Y++;
		g_sChar2.m_cLocation.Y++;
        bSomethingHappened = true;

		
    }
	else if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		g_sChar.m_cLocation.Y++;
		bSomethingHappened = true;

		if (Frame[g_sChar.m_cLocation.X][g_sChar.m_cLocation.Y] == '77')
		{
			g_sChar.m_cLocation.Y--;
		}
	}
	else if (g_abKeyPressed[K_DOWN] && g_sChar2.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
	{
		g_sChar2.m_cLocation.Y++;
		bSomethingHappened = true;
		if (Frame[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == '77')
		{
			g_sChar2.m_cLocation.Y--;
		}
	}
	if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1 && g_sChar2.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;
		g_sChar2.m_cLocation.X++;
        bSomethingHappened = true;

		
    }
	else if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		//g_sChar.m_cLocation.X++;
		bSomethingHappened = true;
		if (Wall1[g_sChar.m_cLocation.X + 1][g_sChar.m_cLocation.Y] == ' ')
		{
			g_sChar.m_cLocation.X++;
		}
	}
	else if (g_abKeyPressed[K_RIGHT] && g_sChar2.m_cLocation.X < g_Console.getConsoleSize().X - 1)
	{
		g_sChar2.m_cLocation.X++;
		bSomethingHappened = true;

		if (Frame[g_sChar2.m_cLocation.X][g_sChar2.m_cLocation.Y] == 'M')
		{
			g_sChar2.m_cLocation.X--;
		}
	}*/
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
		g_sChar2.m_bActive = !g_sChar2.m_bActive;
        bSomethingHappened = true;
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
	
}

void renderMap()
{
	COORD c;
	int bRow = 1;

	myfile.open("border.txt");

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			c.X = 0;
			c.Y = bRow;
			bRow++;
			g_Console.writeToBuffer(c, line, 0x07);
		}
		myfile.close();
	}

	//short Frame[152][2];
	//Store coordinates for the Frame of the Maze
	//Each block will be 50x8
	/*short widthBorderYCoord = 2;//Y coordinates for the sider borders
	for (int i = 0; i < 152; i++)
	{
		if (i < 52)
		{
			Frame[i][0] = i;
			Frame[i][1] = 1;
		}
		else if (i >= 52 && i < 100)
		{
			if (i % 2 == 0)
			{
				Frame[i][0] = 0;//X coordinate for the left border
				Frame[i][1] = widthBorderYCoord;
			}
			else
			{
				Frame[i][0] = 51;//X coordinate for the right border
				Frame[i][1] = widthBorderYCoord;
				widthBorderYCoord++;
			}
		}
		else if (i >= 100)
		{
			Frame[i][0] = (i-100);
			Frame[i][1] = 26;//Y coordinates for the bottom border
		}
	}

	for (int x = 0; x < 152; x++)
	{
		c.X = Frame[x][0];
		c.Y = Frame[x][1];

		g_Console.writeToBuffer(b, "M");

		g_Console.writeToBuffer(c, "M");

	}*/

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
void randMazeTypes(int maze,int row)
{
	COORD mazeC;
	std::string line;
	std::fstream myfile;
	//std::string line;
	//std::fstream myfile;

	switch (maze)
	{
	case 0: myfile.open("map1.txt");
		break;
	case 1: myfile.open("map2.txt");
		break;
	case 2: myfile.open("map3.txt");
		break;
	case 3: myfile.open("map4.txt");
		break;
	case 4: myfile.open("map5.txt");
		break;
	case 5: myfile.open("map6.txt");
		break;
	case 6: myfile.open("map7.txt");
		break;
	case 7: myfile.open("map8.txt");
		break;
	case 8: myfile.open("map9.txt");
		break;
	}
			
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			mazeC.X = 1;
			mazeC.Y = row;
			row++;
			g_Console.writeToBuffer(mazeC, line, 0x05);
		}
		myfile.close();
	}

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
		if (colY <= 2 + (8 * mazenumber))
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

	//char item;
	//short Frame[152][2];
	//for (int i = 0; i < 10; i++)
}

#include <vector>
//Ignore this part first. I will put them into another file when i finish this
//Please put new functions above this.
void moveAI()
{

	/*if (AItime == 0)
	{
		AItime = g_dElapsedTime;
	}
	else

	{
		if (g_dElapsedTime - AItime > 1)
			AItime = 0;
			return;
	}

	COORD AI;
	//[][0] xcoord [][1] ycoord [][2] movementcost [][3]heuristic [][4] findingcost
//	AIPathOpenlist[1024][5];
	//choose from open list to add into close list.
//	AIPathCloselist[1024][2];
//	AIPathfind[1024][5];

	double distChar1;
	double distChar2;

//	AIPrevious.X = g_sAI.m_cLocation.X;
//	AIPrevious.Y = g_sAI.m_cLocation.Y;

	int row = 0, col = 0;
	short AIPathOpenlist[1024][5];
	short AIPathCloselist[1024][2];
	short AIPathfind[80][40] = { 0, };
	int closelistcount = 0;
	int openlistcount = 0;
	int ignopenlistcount = 0;
	int G;//move cost
	int H;//heuristic
	int F;//finding cost
	short heuristictargetX;
	//shortest heuristic X
	short heuristictargetY;
	//shortest heuristic Y

	AI.X = g_sAI.m_cLocation.X;
	AI.Y = g_sAI.m_cLocation.Y;

	AIPathfind[AI.X][AI.Y] = 1;

	distChar1 = distCharToAi(g_sAI.m_cLocation.X, g_sAI.m_cLocation.Y, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y);
	distChar2 = distCharToAi(g_sAI.m_cLocation.X, g_sAI.m_cLocation.Y, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y);
	
	AIPathCloselist[closelistcount][0] = g_sAI.m_cLocation.X;
	AIPathCloselist[closelistcount][1] = g_sAI.m_cLocation.Y;
	closelistcount++;
	
	//Loop needs F = 0 as condition
	//IF dead end, choose the lowest F in open list.
	//OR should i say, Every loop checks for the lowest F and use it instead.
	while (true)
	{
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				//if (Wall1[AI.X + x][AI.Y + y] == ' ')
				//{
					if (x == 0 && y == 0)
						continue;

					bool InOpenlist = false;
					for (int k = openlistcount; k > 0; k--)
					{
						if (AIPathOpenlist[k][0] == AI.X + x && AIPathOpenlist[k][1] == AI.Y + y)
						{
							InOpenlist = true;
							continue;
						}
						
					}
					if (!InOpenlist)
					{
						AIPathOpenlist[openlistcount][0] = AI.X + x;
						AIPathOpenlist[openlistcount][1] = AI.Y + y;



						//Movecost====================================================
						int movecost;
						if (x == 0 && y == -1 || x == -1 && y == 0 || x == 1 && y == 0 || x == 0 && y == 1)
						{
							movecost = 10;
						}
						else
						{
							movecost = 14;
						}
						AIPathOpenlist[openlistcount][2] = movecost;
						//Movecost====================================================

						//Heuristic====================================================

						//calculate the heuristic for the nearer target.
						if (distChar1 < distChar2)
						{
							heuristictargetX = g_sChar.m_cLocation.X; 
							heuristictargetY = g_sChar.m_cLocation.Y;
						}
						else
						{
							heuristictargetX = g_sChar2.m_cLocation.X; 
							heuristictargetY = g_sChar2.m_cLocation.Y;
						}

						AIPathOpenlist[openlistcount][3] = AiPathFindHeuristic(AI.X + x, AI.Y + y, heuristictargetX, heuristictargetY);
						//Heuristic====================================================

						//Findingcost====================================================
						AIPathOpenlist[openlistcount][4] = AIPathOpenlist[openlistcount][2] + AIPathOpenlist[openlistcount][3];
						//Findingcost====================================================


						//If It is in the open list already, Use G to check for better path (diagonal)

						//Terminate, if H = 0, shortest route found, break loop.
						//if (AIPathOpenlist[openlistcount][3] == 0)
						//	break;
						//Here, AI.X and AI.Y node of the shortest route adjacent to the target.



						openlistcount++;
					}
				//}
			}
		}

		//Add shortest node amongst the area to closelist.
		//Reassign new node in shorter finding cost.
<<<<<<< HEAD
		
		int shortestfindscore = 0;
		int shortestScore = 0;
		for (int count = openlistcount - 1; count > ignopenlistcount; count--)
		{
			if (shortestfindscore == 0)
			{
				shortestfindscore = AIPathOpenlist[count][4];
				shortestScore = count;
			}
			else if (AIPathOpenlist[count][4] < shortestfindscore && AIPathOpenlist[count][0] != 0 && AIPathOpenlist[count][1] != 0)
			{
				shortestfindscore = AIPathOpenlist[count][4];
				shortestScore = count;
			}
			if (count == ignopenlistcount)
				ignopenlistcount = openlistcount;

		}
	
		AIPathCloselist[closelistcount][0] = AIPathOpenlist[shortestScore][0];
		AIPathCloselist[closelistcount][1] = AIPathOpenlist[shortestScore][1];
		AIPathOpenlist[shortestScore][0] = 0;
		AIPathOpenlist[shortestScore][1] = 0;
		AIPathOpenlist[shortestScore][2] = 0;
		AIPathOpenlist[shortestScore][3] = 0;
		AIPathOpenlist[shortestScore][4] = 0;
		
//		bool InsideCloselist = false;
		for (int i = 0; i < closelistcount; i++)
		{
			for (int j = ignopenlistcount; j < openlistcount; j++)
			{
				if (AIPathCloselist[i][0] == AIPathOpenlist[j][0] && AIPathCloselist[i][1] == AIPathOpenlist[j][1] && AIPathOpenlist[j][0] != 0 && AIPathOpenlist[j][1] != 0)
				{
//					InsideCloselist = true;
//					break;
					//if any coords in open list is inside closed list, ignore and do not assign as new node.
				}
			}
			//Reassign new node
			
		}

//		if (!InsideCloselist)
//		{
			AI.X = AIPathCloselist[closelistcount][0];
			AI.Y = AIPathCloselist[closelistcount][1];
			closelistcount++;

=======
		
		int shortestfindscore = 0;
		int shortestScore = 0;
		for (int count = openlistcount - 1; count > ignopenlistcount; count--)
		{
			if (shortestfindscore == 0)
			{
				shortestfindscore = AIPathOpenlist[count][4];
				shortestScore = count;
			}
			else if (AIPathOpenlist[count][4] < shortestfindscore && AIPathOpenlist[count][0] != 0 && AIPathOpenlist[count][1] != 0)
			{
				shortestfindscore = AIPathOpenlist[count][4];
				shortestScore = count;
			}
			if (count == ignopenlistcount)
				ignopenlistcount = openlistcount;

		}
	
		AIPathCloselist[closelistcount][0] = AIPathOpenlist[shortestScore][0];
		AIPathCloselist[closelistcount][1] = AIPathOpenlist[shortestScore][1];
		AIPathOpenlist[shortestScore][0] = 0;
		AIPathOpenlist[shortestScore][1] = 0;
		AIPathOpenlist[shortestScore][2] = 0;
		AIPathOpenlist[shortestScore][3] = 0;
		AIPathOpenlist[shortestScore][4] = 0;
		
//		bool InsideCloselist = false;
		for (int i = 0; i < closelistcount; i++)
		{
			for (int j = ignopenlistcount; j < openlistcount; j++)
			{
				if (AIPathCloselist[i][0] == AIPathOpenlist[j][0] && AIPathCloselist[i][1] == AIPathOpenlist[j][1] && AIPathOpenlist[j][0] != 0 && AIPathOpenlist[j][1] != 0)
				{
//					InsideCloselist = true;
//					break;
					//if any coords in open list is inside closed list, ignore and do not assign as new node.
				}
			}
			//Reassign new node
			
		}

//		if (!InsideCloselist)
//		{
			AI.X = AIPathCloselist[closelistcount][0];
			AI.Y = AIPathCloselist[closelistcount][1];
			closelistcount++;

>>>>>>> c3f05c03dfd35846dccb597cb836ce50c34dd217
			AIPathfind[AI.X][AI.Y] = 1;
//		}

		if (AI.X == heuristictargetX && AI.Y == heuristictargetY)
		{
			break;
		}

	}//End of infinite loop
	
	//Trace back

/*	std::vector <int> ShortestRouteCoords;
	for (int traceX = 0; traceX < 80; traceX++)
	{
		for (int traceY = 0; traceY < 40; traceY++)
		{
			if (AIPathfind[traceX][traceY] == 1)
			{
				ShortestRouteCoords.push_back(traceX);
				ShortestRouteCoords.push_back(traceY);
				//[0] = x, [1] = y (even X, odd Y)
			}
		}
	}
	//end trace back

	int shortest = 0;
	int XorY = 0;
	short traceX = 0;
	short traceY = 0;
	short newX;
	short newY;
	
	for (std::vector<int>::iterator it = ShortestRouteCoords.begin(); it != ShortestRouteCoords.end(); ++it)
	{
		if (XorY % 2 == 0)
			traceX = *it;
		else
		{
			traceY = *it;

			if (shortest > distCharToAi(traceX, traceY, heuristictargetX, heuristictargetY))
			{
				shortest = distCharToAi(traceX, traceY, heuristictargetX, heuristictargetY);
				newX = traceX;
				newY = traceY;
			}
		}

<<<<<<< HEAD
	}
	g_sAI.m_cLocation.X = AIPathCloselist[1][0];
	g_sAI.m_cLocation.Y = AIPathCloselist[1][1];
*/
/*
=======
	}
	g_sAI.m_cLocation.X = AIPathCloselist[1][0];
	g_sAI.m_cLocation.Y = AIPathCloselist[1][1];


>>>>>>> c3f05c03dfd35846dccb597cb836ce50c34dd217
	//assign new location for AI
	int shortest = 0;
	for (int closerow = 0; closerow < 80; closerow++)
	{
		for (int closecol = 0; closecol < 80; closecol++)
		{
			if (AIPathCloselist[closerow][closecol] != 0);
//			AIPathCloselist[closerow][closecol] 
//			g_sAI.m_cLocation.X = 		
//			g_sAI.m_cLocation.Y = AIPathCloselist[closerow][1];
		}
		
	}
<<<<<<< HEAD
	*/

//	if (g_sChar.m_cLocation.X && g_sChar.m_cLocation.Y || g_sChar2.m_cLocation.X && g_sChar.m_cLocation.Y)
		

//	if (g_sAI.m_cLocation.Y > 1)
//	{
//		g_sAI.m_cLocation.Y--;
//	}
//	else
//	{
//		g_sAI.m_cLocation.Y++;
//	}


//	if (g_sChar.m_cLocation.X && g_sChar.m_cLocation.Y || g_sChar2.m_cLocation.X && g_sChar.m_cLocation.Y)
		


//	if (g_sAI.m_cLocation.Y > 1)
//	{
//		g_sAI.m_cLocation.Y--;
//	}
//	else
//	{
//		g_sAI.m_cLocation.Y++;
//	}


}
