#include "mazeCoords.h"

void mazeCoords(int mazetype, int mazenumber)
{

	if (mazetype == 0)
	{
		char map1[] = {
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			'�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�',
			'�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�',
			' ', ' ', '�', ' ', ' ', '�', '�', ' ', '�', ' ', '�', '�', '�', ' ', '�', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', ' ', ' ', ' ', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�',
			' ', ' ', '�', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�',
			' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' '
		};
		storeGlobalWall(map1, mazenumber);
	}
	else if (mazetype == 1)
	{
		char map2[] = {
			' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ',
			' ', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', '�', ' ', '�', '�', '�', ' ', '�', ' ', '�', '�', '�', '�',
			' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', ' ', '�', ' ', '�', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ',
			' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ',
			' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ',
			'�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', '�', '�', '�', ' ',
			' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', ' ', ' ', '�', '�', ' ', '�', '�', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', ' ',
			' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ',
		};
		storeGlobalWall(map2, mazenumber);
	}
	else if (mazetype == 2)
	{
		char map3[] = {
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ',
			' ', '�', '�', ' ', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', ' ',
			'�', '�', ' ', ' ', ' ', '�', ' ', '�', '�', ' ', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�',
			' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�',
			'�', '�', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ',
			' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ',
			' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ',
		};
		storeGlobalWall(map3, mazenumber);
	}
	else if (mazetype == 3)
	{
		char map4[] = {
			' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ',
			' ', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', ' ', ' ', '�',
			' ', ' ', '�', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�',
			' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', ' ', ' ', ' ', ' ',
			'�', '�', '�', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', '�', ' ', '�', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', ' ',
			' ', '�', ' ', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ',
		};
		storeGlobalWall(map4, mazenumber);
	}
	else if (mazetype == 4)
	{
		char map5[] = {
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ',
			' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�',
			' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', '�', ' ', ' ',
			'�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ',
			' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ',
			' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
		};
		storeGlobalWall(map5, mazenumber);
	}
	else if (mazetype == 5)
	{
		char map6[] = {
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ',
			' ', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', '�',
			'�', '�', '�', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', '�',
			' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ',
			' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ',
		};
		storeGlobalWall(map6, mazenumber);
	}
	else if (mazetype == 6)
	{
		char map7[] = {
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			'�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ',
			' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�',
			' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ',
			' ', ' ', '�', ' ', ' ', '�', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ',
			' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ',
		};
		storeGlobalWall(map7, mazenumber);
	}
	else if (mazetype == 7)
	{
		char map8[] = {
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ',
			'�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', '�', ' ', ' ', ' ',
			' ', ' ', '�', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', '�', '�',
			' ', ' ', '�', ' ', '�', ' ', ' ', ' ', '�', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
			' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', ' ', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', '�', ' ', '�', '�', '�', '�', ' ', ' ',
			' ', '�', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', '�', ' ', ' ', '�', ' ', '�', '�', ' ',
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', '�', '�', '�', '�', ' ', '�', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
		};
		storeGlobalWall(map8, mazenumber);
	}
	else if (mazetype == 8)
	{
		char map9[] = {
			' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
			' ', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', '�', '�', '�', '�', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ',
			' ', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ',
			' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', ' ', ' ', '�',
			' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', '�',
			' ', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', '�', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�',
			' ', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', '�', '�', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', '�', '�', '�', '�', ' ', '�', '�', '�', '�', '�', ' ', '�', '�', ' ', ' ',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', '�', ' ', ' ', ' ', ' ', ' ', ' ', '�', ' ', ' ',
		};
		storeGlobalWall(map9, mazenumber);
	}
}
