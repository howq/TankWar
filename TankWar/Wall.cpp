#include "stdafx.h"
#include "Wall.h"


CWall::CWall()
{
	start = time(NULL);
	live = 1;
	order = 4;
	level = 0;
	dir = direction(0);
	isDead = false;
}


CWall::~CWall()
{
}

void CWall::TimeEnd(time_t stop)
{
	if (stop - start >= 10)
	{
		isDead = true;
	}
}