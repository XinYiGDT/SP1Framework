#include "Pup.h"
#include "Framework\console.h"
#include <iomanip>

extern Console g_Console;
extern double gameTime;
extern SGameChar g_sChar;
extern SGameChar g_sChar2;
extern SGamePup g_sPup;
extern char MazeMap[40][80];
extern bool checkloca;
extern double g_dElapsedTime;
extern double addScore;
extern double reactiontime;
extern double AIreactiontime;
double Puptimer;
int Pupcheck = 0;
bool Pup3active = false;
bool Pup4active = false;
bool Pup5active = false;
bool Pup6active = false;
bool Pup7active = false;
bool Pup8active = false;
bool stringactive = false;
int randpupnumber;

void renderPup()
{

	short PuprandPointX;
	short PuprandPointY;


	if (g_sChar.m_cLocation.X == g_sPup.m_cLocation.X && g_sChar.m_cLocation.Y == g_sPup.m_cLocation.Y ||
		g_sChar2.m_cLocation.X == g_sPup.m_cLocation.X && g_sChar2.m_cLocation.Y == g_sPup.m_cLocation.Y) //check collision
	{
		Puprand();
		g_sPup.m_bActive = false;

		stringactive = true;
	}

	if (g_sPup.m_bActive == false) //spawn random point
	{
		while (true)
		{
			PuprandPointX = rand() % 50 + 1;
			PuprandPointY = rand() % 24 + 2;
			if (MazeMap[PuprandPointY][PuprandPointX] != 'M' && MazeMap[PuprandPointY][PuprandPointX] != (char)219)
			{
				g_sPup.m_cLocation.X = PuprandPointX;
				g_sPup.m_cLocation.Y = PuprandPointY;
				break;
			}
		}
		g_sPup.m_bActive = true;
	}
	g_Console.writeToBuffer(g_sPup.m_cLocation, "@");

	if (stringactive == true)
	{
		std::string Puptypestr;
		switch (randpupnumber)
		{
		case 0:Puptypestr = "Time Added";
			break;
		case 1:Puptypestr = "Time Deducted";
			break;
		case 2:Puptypestr = "MULTIPLIER";
			break;
		case 3:Puptypestr = "DECLINER";
			break;
		case 4:Puptypestr = "Player speed Increase";
			break;
		case 5:Puptypestr = "Player speed Decrease";
			break;
		case 6:Puptypestr = "AI speed Increase";
			break;
		case 7:Puptypestr = "AI speed Decrease";
			break;
		}
		COORD Puptypecoord;
		Puptypecoord.X = 52 / 2 - Puptypestr.length() / 2;
		Puptypecoord.Y = 30;
		g_Console.writeToBuffer(Puptypecoord, Puptypestr);
	}
}

void updatePup()
{
	if (Pup3active == true) //activate Pup3 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup3active = false;
			addScore -= 5;
			stringactive = false;
		}
	}

	if (Pup4active == true) //activate Pup4 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup4active = false;
			addScore += 5;
			stringactive = false;
		}
	}

	if (Pup5active == true) //activate Pup5 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup5active = false;
			reactiontime = 0.125;
			stringactive = false;
		}
	}

	if (Pup6active == true) //activate Pup6 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup6active = false;
			reactiontime = 0.125;
			stringactive = false;
		}
	}

	if (Pup7active == true) //activate Pup7 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup7active = false;
			AIreactiontime = 0.5;
			stringactive = false;
		}
	}

	if (Pup8active == true) //activate Pup8 for 5 sec
	{
		if (g_dElapsedTime - Puptimer > 1)
		{
			Puptimer = g_dElapsedTime;
			Pupcheck++;
		}
		else
		{
			return;
		}

		if (Pupcheck == 6)
		{
			Pupcheck = 0;
			Pup8active = false;
			AIreactiontime = 0.5;
			stringactive = false;
		}
	}
}

void Puprand()
{
	srand(time(NULL));
	randpupnumber = rand() % 8;

	switch (randpupnumber)
	{
	case 0: Pup();
		break;
	case 1: Pup2();
		break;
	case 2: Pup3();
		break;
	case 3: Pup4();
		break;
	case 4: Pup5();
		break;
	case 5: Pup6();
		break;
	case 6: Pup7();
		break;
	case 7: Pup8();
		break;
	}
}

void Pup() //add time
{
	gameTime += 10;
}

void Pup2() //decrease time
{
	gameTime -= 10;
}

void Pup3() //score bonus
{
	addScore += 5;
	Pup3active = true;
}

void Pup4() //score deduction
{
	addScore -= 5;
	Pup4active = true;
}

void Pup5() //speed up characters
{
	reactiontime = 0.05;
	Pup5active = true;
}

void Pup6() //slow down characters
{
	reactiontime = 0.5;
	Pup6active = true;
}

void Pup7() //speed up AI
{
	AIreactiontime = 0.2;
	Pup7active = true;
}

void Pup8() //slow down AI
{
	AIreactiontime = 0.8;
	Pup8active = true;
}