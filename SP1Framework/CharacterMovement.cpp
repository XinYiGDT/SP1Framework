#include "CharacterMovement.h"

extern SGameChar g_sChar;
extern SGameChar g_sChar2;
extern bool bSomethingHappened;
extern char MazeMap[40][80];

void characterMovement(short direction)
{


	if (direction == 2)//UP
	{
		bSomethingHappened = true;

		//Check if next location is obstructed. If not, move to that location.
		if (!(MazeMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == 'M' || MazeMap[g_sChar.m_cLocation.Y - 1][g_sChar.m_cLocation.X] == (char)219))
		{
			g_sChar.m_cLocation.Y--;
		}
		if (!(MazeMap[g_sChar2.m_cLocation.Y - 1][g_sChar2.m_cLocation.X] == 'M' || MazeMap[g_sChar2.m_cLocation.Y - 1][g_sChar2.m_cLocation.X] == (char)219))
		{
			g_sChar2.m_cLocation.Y--;
		}


	}
	if (direction == 3)//DOWN
	{
		g_sChar.m_cLocation.Y++;
		g_sChar2.m_cLocation.Y++;
		bSomethingHappened = true;

		if (MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' || MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)219)
		{
			g_sChar.m_cLocation.Y--;
		}
		if (MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M' || MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == (char)219)
		{
			g_sChar2.m_cLocation.Y--;
		}
	}
	if (direction == 0) //LEFT
	{
		g_sChar.m_cLocation.X--;
		g_sChar2.m_cLocation.X--;
		bSomethingHappened = true;

		if (MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' || MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)219)
		{
			g_sChar.m_cLocation.X++;
		}
		if (MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M' || MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == (char)219)
		{
			g_sChar2.m_cLocation.X++;
		}
	}
	if (direction == 1) //RIGHT
	{
		g_sChar.m_cLocation.X++;
		g_sChar2.m_cLocation.X++;
		bSomethingHappened = true;

		if (MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == 'M' || MazeMap[g_sChar.m_cLocation.Y][g_sChar.m_cLocation.X] == (char)219)
		{
			g_sChar.m_cLocation.X--;
		}
		if (MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == 'M' || MazeMap[g_sChar2.m_cLocation.Y][g_sChar2.m_cLocation.X] == (char)219)
		{
			g_sChar2.m_cLocation.X--;
		}
	}


}