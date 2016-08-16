#include "isCollision.h"

bool isCollision(SGameChar chara, SGameChar chara2)
{
	int dist;

	dist = abs(sqrt(sqrt(chara.m_cLocation.X - chara2.m_cLocation.X) + sqrt(chara.m_cLocation.Y - chara2.m_cLocation.Y)));


	if (chara.m_cLocation.X == isascii(32) || chara.m_cLocation.Y == isascii(32))
	{
		return true;
	}
	if (chara2.m_cLocation.X == isascii(32) || chara2.m_cLocation.Y == isascii(32))
	{
		return true;
	}
	return false;
}