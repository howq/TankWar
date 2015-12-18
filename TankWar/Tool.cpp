#include "stdafx.h"
#include "Tool.h"


CTool::CTool()
{
	start = time(NULL);
	order = 1;
	dir = direction(0);
	isDead = false;
	live = 1;
}

CTool::~CTool()
{
}

void CTool::InitPos(int currX, int currY, int levl)
{
	coord = cvPoint(currX, currY);
	level = levl;
}

void CTool::TimeEnd(time_t stop)
{
 	if (stop -start>=8)
	{
		isDead = true;
	}
}

/*
	time_t start, stop;
	start = time(NULL);
	foo();//dosomething
	stop = time(NULL);
	printf("Use Time:%ld\n", (stop - start));*/