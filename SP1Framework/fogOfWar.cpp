#include "fogOfWar.h"

using namespace std;
COORD c;

void renderFog( SGameChar *g_sChar, SGameChar *g_sChar2, Console *g_Console, char fog1[40][80])
{
	c.X = 0;
	c.Y = 1;
	int temp = c.X;

	char fog2[40][80];

	//view range
	short viewRange = 3;
	
	memset(fog2, '\0', sizeof(fog2[0][0]) * 40 * 80);

	//check player position for rendering
	for (short x = g_sChar->m_cLocation.X - viewRange - 1; x < g_sChar->m_cLocation.X + viewRange + 1; x++)
	{
		for (short y = g_sChar->m_cLocation.Y - viewRange + 1; y < g_sChar->m_cLocation.Y + viewRange - 2; y++)
		{
			if (x < 0)
			{
				continue;
			}
			if (y < 0)
			{
				continue;
			}

			fog1[y][x] = MazeMap[y+1][x];
			fog2[y][x] = fog1[y][x];
		}
	}

	//render fog with map
	for (int row = 0; row < 40; row++)
	{
		for (int col = 0; col < 80; col++)
		{
			if (fog1[row][col] == '\0' || fog1[row][col] == '\n')
			{
				break;
			}

			g_Console->writeToBuffer(c, fog1[row][col], 0x08);

			if (fog2[row][col] != '\0')
			{
				g_Console->writeToBuffer(c, fog2[row][col], 0x0d);
			}

			c.X++;
		}
		c.X = temp;
		c.Y++;
	}

}