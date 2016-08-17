#include "AiPathFindHeuristic.h"

int AiPathFindHeuristic(short Ax, short Ay, short Bx, short By)
{
	int heuristic;
	short xdis;
	short ydis;
	(Ax > Bx) ? (xdis = Ax - Bx) : (xdis = Bx - Ax);
	(Ay > By) ? (ydis = Ay - By) : (ydis = By - Ay);
	xdis *= 10;
	ydis *= 10;

	heuristic = xdis + ydis;
	return heuristic;
}