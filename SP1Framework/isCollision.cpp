#include "isCollision.h"

bool isCollision(SGameChar chara, SGameChar chara2, short frame)
{
	//int dist;
	char border = 'Û';

	/*dist = abs(sqrt(sqrt(chara.m_cLocation.X - chara2.m_cLocation.X) + sqrt(chara.m_cLocation.Y - chara2.m_cLocation.Y)));
	if (dist <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/


	if ((chara.m_cLocation.X + 1) == border || (chara.m_cLocation.Y + 1) == border)
	{
		return true;
	}
	if (chara2.m_cLocation.X == border || chara2.m_cLocation.Y == border)
	{
		return true;
	}
	return false;
}