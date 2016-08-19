#include "distCharToAi.h"
#include <cmath>
double distCharToAi(short Ax, short Ay, short Bx, short By)
{
	double distance;
	distance = sqrt(pow((Ax - Bx), 2) + pow((Ay - By), 2));

	return distance;
}