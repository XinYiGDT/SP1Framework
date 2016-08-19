#include "AiPathFindHeuristic.h"

int AiPathFindHeuristic(short Ax, short Ay, short Bx, short By)
{
	int heuristic;

	heuristic = min(abs(Ax - Bx), abs(Ay - By)) * 14 + abs(abs(Ax - Bx) - abs(Ay - By)) * 10;

	return heuristic;
}