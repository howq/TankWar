#include "stdafx.h"

CFire::CFire()
{
	order = 4;
}


CFire::~CFire()
{
}

void CFire::Move()
{
	if (level == 0){ speed = cvPoint(FIRESPEEDX_LEVEL0, FIRESPEEDY_LEVEL0); }
	if (level == 1){ speed = cvPoint(FIRESPEEDX_LEVEL1, FIRESPEEDY_LEVEL1); }
	switch (dir)
	{
	case left:coord.x -= speed.x;
		break;
	case up:coord.y -= speed.y;
		break;
	case down:coord.y += speed.y;
		break;
	case right:coord.x += speed.x;
		break;
	};

	//2.ÔË¶¯Ô¼Êø
	if (coord.x >= BACKGROUND_WIDHT - FIRE_WIDHT)
	{
		coord.x = BACKGROUND_WIDHT - FIRE_WIDHT;
		isDead = true;
	}
	if (coord.x <= 0)
	{
		coord.x = 0;
		isDead = true;
	}
	if (coord.y >= BACKGROUND_HEIGHT - FIRE_HEIGHT)
	{
		coord.y = BACKGROUND_HEIGHT - FIRE_HEIGHT;
		isDead = true;
	}
	if (coord.y <= 0)
	{
		coord.y = 0;
		isDead = true;
	}
}

void CFire::InitPos(int currX, int currY, int levl,direction direc)
{
	dir = direc;
	coord = cvPoint(currX, currY);
	level = levl;
}

void CFire::ShootDie(CBase * &item)
{
	if (item->IsDeath())return ;

	int fx1 = coord.x;
	int fy1 = coord.y;
	int fw = FIRE_WIDHT;
	int fh = FIRE_HEIGHT;
	int fx2 = 0;
	fx2 = fx1 + fw;
	int fy2 = 0;
	fy2 = fy1 + fh;

	int tx1 = item->GetCurrPosition().x;
	int ty1 = item->GetCurrPosition().y;
	int tw = item->GetCurrWidth();
	int th = item->GetCurrHeight();
	int tx2 = 0;
	tx2 = tx1 + tw;
	int ty2 = 0;
	ty2 = ty1 + th;

	bool wflag = (abs(fx1 + fx2 - tx1 - tx2) <= (tw + fw));
	bool hflag = (abs(fy1 + fy2 - ty1 - ty2) <= (th + fh));

	if (wflag&&hflag)
	{
		isDead = true;
		int itemLevel = item->GetLevel();
		int itemLive = item->GetLive();
		if (itemLevel - level <= 0)
		{
			item->SetLive(itemLive - 1);
		}
		else
		{
			item->SetLevel(0);
		}
		itemLive = item->GetLive();
		if (itemLive < 1)
		{
			item->SetDie(true);
		}
	}
}
