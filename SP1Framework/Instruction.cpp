#include "game.h"
#include "Framework\console.h"

extern Console g_Console;
COORD instCs[5];
std::string inststr[6];
extern bool g_abKeyPressed[K_COUNT];
extern EGAMESTATES g_eGameState;

void Instruction()
{
	inststr[0] = "Use Arrow keys to move Characters";
	inststr[1] = "Let the characters collide to increase score multiplier";
	inststr[2] = "Avoid enemies";
	inststr[3] = "If collided with enemy AI, you have to complete a snake game to continue";
	inststr[4] = "Otherwise you lose the game";
	inststr[5] = "Press Esc to exit to main menu";

	
	for (int i = 0; i < 6; i++)
	{
		instCs[i].X = g_Console.getConsoleSize().X / 2 - inststr[i].length() / 2;
		instCs[i].Y = g_Console.getConsoleSize().Y / 2 - 2 + i;
	}

	if (g_abKeyPressed[K_ESCAPE])
	{
		g_eGameState = S_SELECT;
	}
}
void renderInstruction()
{
	for (int i = 0; i < 6; i++)
	{
		g_Console.writeToBuffer(instCs[i], inststr[i]);
	}
}