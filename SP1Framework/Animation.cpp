#include "Animation.h"

using namespace std;

extern Console g_Console;

//[txt][x][y]
char AnimationArray[4][150][150];
char indexChar;

void readAnimation()
{
	char StringToLoad;

	int row = 0;
	int col = 0;

	string frameLoad[4];

	frameLoad[0] = "Animation/Boy1.txt";
	frameLoad[1] = "Animation/Boy2.txt";
	frameLoad[2] = "Animation/Girl1.txt";
	frameLoad[3] = "Animation/Girl2.txt";

	for (int i = 0; i < 4; i++)
	{
		//fstream::in = input
		fstream find(frameLoad[i], fstream::in);

		//noskipws = Do not skip whitespaces
		while (find >> noskipws >> StringToLoad)
		{
			indexChar = StringToLoad;
			if ((indexChar == '\n') || (indexChar == '\0'))
			{
				col = 0;
				row++;
				continue;
			}

			AnimationArray[i][row][col] = indexChar;
			col++;
		}

		find.close();
		row = 0;
		col = 0;
	}

}

void renderAnimation(int keyFrame, COORD animationC)
{
	COORD animationC2;
	int tempX = animationC.X;

	for (animationC2.Y = 0; animationC2.Y < 150; animationC2.Y++)
	{
		for (animationC2.X = 0; animationC2.X < 150; animationC2.X++)
		{
			char pix;
			if ((AnimationArray[keyFrame][animationC2.Y][animationC2.X] == '\0') || (AnimationArray[keyFrame][animationC2.Y][animationC2.X] == '\n'))
			{
				break;
			}
			else
			{
				pix = AnimationArray[keyFrame][animationC2.Y][animationC2.X];
				if (AnimationArray[keyFrame][animationC2.Y][animationC2.X] != ' ')
				{
					g_Console.writeToBuffer(animationC, pix, 0xFF);
				}
				else
				{
					g_Console.writeToBuffer(animationC, pix, 0x0D);
				}
			}
			
			animationC.X++;
		}

		animationC.X = tempX;
		animationC.Y++;
	}
	//animationC.Y = tempY/15;
}