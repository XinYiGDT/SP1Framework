#include "AIPathFind.h"
#include "Framework\console.h"
#include <cmath>
#include <numeric>


extern Console g_Console;
extern SGameChar g_sChar;
extern SGameChar g_sChar2;
double viewRangeDirectionVec[2];


void AiViewRange(struct SGameBots *Ai)
{
	int dirvecX = 0, dirvecY = 0;

	if (Ai->g_bDirection == B_LEFT)
		dirvecX = -1;
	if (Ai->g_bDirection == B_RIGHT)
		dirvecX = 1;
	if (Ai->g_bDirection == B_UP)
		dirvecY = -1;
	if (Ai->g_bDirection == B_DOWN)
		dirvecY = 1;
	//changes vector direction base on the direction the AI is moving	


	int dirVec[2] = { dirvecX, dirvecY };
	bool Char1inView = false;
	bool Char2inView = false;

	viewRangeDirectionVec[0] = (dirVec[0] / sqrt(pow(dirVec[0], 2) + pow(dirVec[1], 2)));
	viewRangeDirectionVec[1] = (dirVec[1] / sqrt(pow(dirVec[0], 2) + pow(dirVec[1], 2))); //Stores unit vector of view cone.

	double distChar1 = distCharToAi(Ai->m_cLocation.X, Ai->m_cLocation.Y, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y);
	double distChar2 = distCharToAi(Ai->m_cLocation.X, Ai->m_cLocation.Y, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y);



	for (int i = 0; i < 2; ++i)
	{
		int targetVec[2];

		if (i == 0)
		{
			targetVec[0] = (g_sChar.m_cLocation.X - Ai->m_cLocation.X);
			targetVec[1] = (g_sChar.m_cLocation.Y - Ai->m_cLocation.Y);

			if (distChar1 > 10)
			{
				Char1inView = false;
				continue;
			}

			double targetVecLen = sqrt(pow(targetVec[0], 2) + pow(targetVec[1], 2));

			double result;
			double ans = std::inner_product(targetVec, targetVec + 2, viewRangeDirectionVec, 0.0);
			ans /= targetVecLen;
			result = acos(ans) * 180 / 3.14159265;


			if (result <= 26.56505118)
			{
				Char1inView = true;
				Ai->PathfindToChar = true;
				Ai->PathfindCoord.X = g_sChar.m_cLocation.X;
				Ai->PathfindCoord.Y = g_sChar.m_cLocation.Y;
			}
			else
			{
				Char1inView = false;
			}
		}
		else
		{
			targetVec[0] = (g_sChar2.m_cLocation.X - Ai->m_cLocation.X);
			targetVec[1] = (g_sChar2.m_cLocation.X - Ai->m_cLocation.X);

			if (distChar2 > 10)
			{
				Char2inView = false;
				continue;
			}
			double targetVecLen = sqrt(pow(targetVec[0], 2) + pow(targetVec[1], 2));

			double result;
			double ans = std::inner_product(targetVec, targetVec + 2, viewRangeDirectionVec, 0.0);
			ans /= targetVecLen;
			result = acos(ans) * 180 / 3.14159265;

			if (result <= 26.56505118)
			{
				Char2inView = true;
				Ai->PathfindToChar = true;
				Ai->PathfindCoord.X = g_sChar2.m_cLocation.X;
				Ai->PathfindCoord.Y = g_sChar2.m_cLocation.Y;
			}
			else
			{
				Char2inView = false;
			}
		}

	}

}
