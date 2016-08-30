#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "storeMazeMap.h"
#include "AiPathFindHeuristic.h"
#include "distCharToAi.h"
#include "AIPathFind.h"
#include "CharacterMovement.h"
#include "score.h"
#include "gameState.h"
#include "Animation.h"
#include "fogOfWar.h"
#include "Pup.h"
#include "TetrisMinigame.h"
#include "puzzle.h"
extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
	K_DOWN,
	K_LEFT,
	K_RIGHT,
	K_ESCAPE,
	K_SPACE,
	K_R,
	K_Z,
	K_C,
	K_COUNT,
	K_ENTER
};

// Enumeration for the different screen states
enum EGAMESTATES
{
	S_SPLASHSCREEN,
	S_GAME,
	S_INSTRUCTIONS,
	S_SNAKE,
	S_MGAME_TETRIS,
	S_COUNT,
	S_GAMEOVER,
	S_SELECT,
	S_CREDIT
};

// struct for the game character
struct SGameChar
{
	COORD m_cLocation;
	bool  m_bActive;
};

//struct for the game bots
enum BOTSDIRECTION
{
	B_LEFT,
	B_RIGHT,
	B_UP,
	B_DOWN
};

struct SGameBots
{
	COORD m_cLocation;
	COORD g_bRoamAreaA;//game bot roam area. checks if location is more than g_bRoamArea.X or g_bRoamArea.Y
	COORD g_bRoamAreaB;
	BOTSDIRECTION g_bDirection;
	bool PathfindToChar;
	COORD PathfindCoord;
	bool  m_bActive;
};


struct SGamePup
{
	COORD m_cLocation;
	bool m_bActive = false;
};



void init(void);      // initialize your variables, allocate memory, etc
void getInput(void);      // get input from player
void update(double dt); // update the game and the state of the game
void render(void);      // renders the current state of the game to the console
void shutdown(void);      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void randMazeTypes(int maze, int row);// generates the map
void renderAI();            // AI control
void moveAI();

void renderTime();//renders time

void renderAI();            // AI control
void moveAI();

void sound();

void gameOver();
void renderFog( SGameChar *g_sChar, SGameChar *g_sChar2, Console *g_Console, char fog1[40][80]);

void Instuctions();
void renderInstruction();
#endif // _GAME_H