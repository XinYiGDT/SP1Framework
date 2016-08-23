#include "AIPathFind.h"

void AiPresenceArea(struct SGameBots *Ai)
{
	if (Ai->m_cLocation.X <= Ai->g_bRoamAreaA.X)
	{
		Ai->g_bDirection = B_RIGHT;
		Ai->m_cLocation.X++;
		Ai->PathfindToChar = false;
	}
	if (Ai->m_cLocation.X >= Ai->g_bRoamAreaB.X)
	{
		Ai->g_bDirection = B_LEFT;
		Ai->m_cLocation.X--;
		Ai->PathfindToChar = false;
	}
	if (Ai->m_cLocation.Y <= Ai->g_bRoamAreaA.Y)
	{
		Ai->g_bDirection = B_DOWN;
		Ai->m_cLocation.Y++;
		Ai->PathfindToChar = false;
	}
	if (Ai->m_cLocation.Y >= Ai->g_bRoamAreaB.Y)
	{
		Ai->g_bDirection = B_UP;
		Ai->m_cLocation.Y--;
		Ai->PathfindToChar = false;
	}
}