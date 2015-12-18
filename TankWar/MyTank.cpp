#include "stdafx.h"
#include "MyTank.h"


CMyTank::CMyTank()
{
	coord = cvPoint(0, 200);
	order = 4;
	level = 0;
	dir = right;
	isDead = false;
	live = 2;
}


CMyTank::~CMyTank()
{
}

void CMyTank::Move()
{
	if (level == 0){ speed = cvPoint(TANKSPEEDX_LEVEL0, TANKSPEEDY_LEVEL0); }
	if (level == 1){ speed = cvPoint(TANKSPEEDX_LEVEL1, TANKSPEEDY_LEVEL1); }
	switch (key)
	{
	case 'w':
		coord.y -= speed.y;
		dir = up;
		break;
	case 'a':
		coord.x -= speed.x;
		dir = left;
		break;
	case 's':
		coord.y += speed.y;
		dir = down;
		break;
	case 'd':
		coord.x += speed.x;
		dir = right;
		break;
	case 32:
		CreatFire();
	default:break;
	}

	//2.ÔË¶¯Ô¼Êø
	if (coord.x < 620)
	{
		if (coord.x > 540)
		{
			coord.x = 540;
		}
		if (coord.x < speed.x)
		{
			coord.x = 0;
		}
		if (coord.y > 540)
		{
			coord.y = 540;
		}
		if (coord.y < speed.y)
		{
			coord.y = 0;
		}
	} 
}

// MyTank Get Tool
bool CMyTank::GetTool(CTool * &tool)
{
	int fx1 = coord.x;
	int fy1 = coord.y;
	int fw = TOOL_WIDHT;
	int fh = TOOL_HEIGHT;
	int fx2 = 0;
	fx2 = fx1 + fw;
	int fy2 = 0;
	fy2 = fy1 + fh;

	int tx1 = tool->GetCurrPosition().x;
	int ty1 = tool->GetCurrPosition().y;
	int tw = tool->GetCurrWidth();
	int th = tool->GetCurrHeight();
	int tx2 = 0;
	tx2 = tx1 + tw;
	int ty2 = 0;
	ty2 = ty1 + th;

	bool wflag = (abs(fx1 + fx2 - tx1 - tx2) <= (tw + fw));
	bool hflag = (abs(fy1 + fy2 - ty1 - ty2) <= (th + fh));

	if (wflag&&hflag)
	{
		return true;
		tool->SetDie(true);
	}
	else
	{
		return false;
	}
}


