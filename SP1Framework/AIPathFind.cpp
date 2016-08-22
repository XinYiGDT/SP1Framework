#include "AIPathFind.h"

extern SGameChar g_sChar;
extern SGameChar g_sChar2;
extern char MazeMap[40][80];

void AIPathFind(SGameChar *OriginalAi)
{
	COORD AI;

	double distChar1;
	double distChar2;

	//AiPathList can hold both close and open list. size relies on map width and height
	short AIPathList[27][52][6];//[0]close/open, [1]G [2]H [3]F [4]ParentY [5]ParentX

	int shortestH = 0;//heuristic
	int shortestF = 0;//finding cost
	short shortestF_X;
	short shortestF_Y;
	short heuristictargetX;//shortest heuristic X
	short heuristictargetY;//shortest heuristic Y

	AI.X = OriginalAi->m_cLocation.X;
	AI.Y = OriginalAi->m_cLocation.Y;

	distChar1 = distCharToAi(OriginalAi->m_cLocation.X, OriginalAi->m_cLocation.Y, g_sChar.m_cLocation.X, g_sChar.m_cLocation.Y);
	distChar2 = distCharToAi(OriginalAi->m_cLocation.X, OriginalAi->m_cLocation.Y, g_sChar2.m_cLocation.X, g_sChar2.m_cLocation.Y);

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

	AIPathList[AI.Y][AI.X][0] = 'o';//[0]close/open, [1]G [2]H [3]F    'o' == 111, 'c' == 99
	AIPathList[AI.Y][AI.X][1] = 0;
	AIPathList[AI.Y][AI.X][2] = AiPathFindHeuristic(AI.X, AI.Y, heuristictargetX, heuristictargetY);
	AIPathList[AI.Y][AI.X][3] = AIPathList[AI.Y][AI.X][2] + AIPathList[AI.Y][AI.X][1];
	AIPathList[AI.Y][AI.X][4] = AI.Y;//Parent of startnode is itself
	AIPathList[AI.Y][AI.X][5] = AI.X;

	while (true)
	{
		shortestF = 0;
		for (int AiY = 0; AiY < 27; AiY++)
		{
			for (int AiX = 0; AiX < 52; AiX++)
			{
				if (AIPathList[AiY][AiX][0] == 'o')//if only in open list
				{
					if (shortestF == 0)
					{
						shortestF = AIPathList[AiY][AiX][3];
						shortestF_X = AiX;
						shortestF_Y = AiY;
					}
					else if (shortestF > AIPathList[AiY][AiX][3])
					{
						shortestF = AIPathList[AiY][AiX][3];
						shortestF_X = AiX;
						shortestF_Y = AiY;
					}
					//Finds shortest F.
				}
			}
		}

		AIPathList[shortestF_Y][shortestF_X][0] = 'c';//add shortest F to close list.
		AI.X = shortestF_X;
		AI.Y = shortestF_Y;

		if (shortestF_X == heuristictargetX && shortestF_Y == heuristictargetY)
		{
			break;//path has been found if X and Y == to target
		}

		//		bool gotWall = false;
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{

				if (x == 0 && y == 0)
					continue;

				if (MazeMap[AI.Y + y][AI.X + x] == 'M' || MazeMap[AI.Y + y][AI.X + x] == '#')//If there is a wall, ignore
				{
					continue;
				}

				//Prevent Corner cutting============================================
				if (((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1)) && (MazeMap[AI.Y][AI.X + x] == '#')		//-- 0- +-
					|| ((x == -1 && y == -1) || (x == 1 && y == -1) || (x == -1 && y == 1) || (x == 1 && y == 1)) && (MazeMap[AI.Y + y][AI.X] == '#'))		//-0 00 +0
				{																																			//-+ 0+ ++
					continue;																																//if there is wall adjacent to the tile,
				}																																			//in (x=0) OR (y=0), ignore
				//Eg. for (x-,y-)
				//check if (x,y-) OR (x-,y) have walls
				//if true, ignore that diagonal	

				if (AIPathList[AI.Y + y][AI.X + x][0] == 'c')//if neighbour is in closelist, ignore.
					continue;

				if (AIPathList[AI.Y + y][AI.X + x][0] != 'o' && AIPathList[AI.Y + y][AI.X + x][0] != 'c'
					|| AIPathList[AI.Y + y][AI.X + x][3] < shortestF)//if neighbour is not in OPEN OR new path to neighbour is shorter
				{
					//Movecost====================================================
					if (x == 0 && y == -1 || x == -1 && y == 0 || x == 1 && y == 0 || x == 0 && y == 1)
					{//Horizontal/Vertical
						AIPathList[AI.Y + y][AI.X + x][1] = 10 + AIPathList[AI.Y][AI.X][1];
					}
					else
					{//Diagonals
						AIPathList[AI.Y + y][AI.X + x][1] = 14 + AIPathList[AI.Y][AI.X][1];
					}
					//Movecost====================================================

					//Heuristic====================================================
					AIPathList[AI.Y + y][AI.X + x][2] = AiPathFindHeuristic(AI.X + x, AI.Y + y, heuristictargetX, heuristictargetY);
					//Heuristic====================================================

					//Findingcost====================================================
					AIPathList[AI.Y + y][AI.X + x][3] = AIPathList[AI.Y + y][AI.X + x][2] + AIPathList[AI.Y + y][AI.X + x][1];
					//Findingcost====================================================

					//Set Parent of neighbour=========================================
					AIPathList[AI.Y + y][AI.X + x][4] = AI.Y;
					AIPathList[AI.Y + y][AI.X + x][5] = AI.X;
					//Set Parent of neighbour=========================================

					if (AIPathList[AI.Y + y][AI.X + x][0] != 'o')
						AIPathList[AI.Y + y][AI.X + x][0] = 'o';

				}
			}
		}
	}
	//infinite loop ends here ---------------------------------------------------

	//Trace back
	while (true)
	{
		short tempX;
		short tempY;
		//If parent of shortF nodes is initial location of AI, break.
		if (AIPathList[shortestF_Y][shortestF_X][5] == OriginalAi->m_cLocation.X && AIPathList[shortestF_Y][shortestF_X][4] == OriginalAi->m_cLocation.Y)
			break;
		//Reassign parent from the end node. shortestF_X and _Y ended when pathfinding hits target
		tempX = AIPathList[shortestF_Y][shortestF_X][5];
		tempY = AIPathList[shortestF_Y][shortestF_X][4];

		shortestF_X = tempX;
		shortestF_Y = tempY;
	}

	OriginalAi->m_cLocation.X = shortestF_X;
	OriginalAi->m_cLocation.Y = shortestF_Y;

}

//Open .. The set of nodes to be evaluated
//Closed .. The set of nodes already evaluated
//Add the start node to open

//loop
//current .. node in the OPEN with the lowest F cost
//remove current from OPEN
//add current to CLOSED

//if current is the target node (path has been found)
//return

//for each neighbour of the current node
//	if neighbour is not traversable or neighbour is in CLOSED
//	skip to next neighbour

//if new path to neighbour is shorter OR neighbour is not in OPEN
//	set F cost of neighbour
//	set parent of neighbour to current
//	if neighbour is not in OPEN
//		add neighbour to OPEN.
