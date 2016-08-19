/*#include "CharacterMovement.h"

void characterMovement()
{

	extern SGameChar   g_sChar;
	extern SGameChar   g_sChar2;


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

}*/