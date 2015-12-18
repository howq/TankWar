#include "stdafx.h"


CTank::CTank()
{
	order = 4;
	int i = rand() % 2;
	level = i;
	i = rand()%2;
	switch (i)
	{
	case 0:	coord = cvPoint(BACKGROUND_WIDHT - TANK_WIDHT, 0); break;
	case 1:	coord = cvPoint(BACKGROUND_WIDHT - TANK_WIDHT, BACKGROUND_HEIGHT - TANK_HEIGHT); break;
	default:
		break;
	}
	dir = direction(rand() % 4);
	isDead = false;
	live = 1;
}

CTank::~CTank()
{
}

void CTank::Move()
{
	//1.按规则运动
	if (level == 0){ speed = cvPoint(TANKSPEEDX_LEVEL0, TANKSPEEDY_LEVEL0); }
	if (level == 1){ speed = cvPoint(TANKSPEEDX_LEVEL1, TANKSPEEDY_LEVEL1); }
	switch (dir)
	{
	case up:
		coord.y -= speed.y;
		break;
	case left:
		coord.x -= speed.x;
		break;
	case down:
		coord.y += speed.y;
		break;
	case right:
		coord.x += speed.x;
		break;
	}

	//2.运动约束

	int chance = rand() % 60;		//moving change direction
	if (0 == chance)
	{
		dir = direction(rand() % 4);
	}

	if (coord.x >= 540)
	{
		coord.x = 540;
		while (dir==right)
		{
			dir = direction(rand() % 4);
		}
	}
	if (coord.x <= 0)
	{
		coord.x = 0;
		while (dir==left)
		{
			dir = direction(rand() % 4);
		}
	}
	if (coord.y >= 540)
	{
		coord.y = 540;
		while (dir == down)
		{
			dir = direction(rand() % 4);
		}
	}
	if (coord.y <= 0)
	{
		coord.y = 0;
		while (dir == up)
		{
			dir = direction(rand() % 4);
		}
	}

	if (rand() % 60 == 0)
	{
		CreatFire();
	}
}

void CTank::InitFireImage(IplImage ** img)
{
	fireImg = img;
}

void CTank::CreatFire()
{
	CFire * fire = new CFire();
	fire->Init(fireImg);
	fire->SetLevel(level);
	int skew = 1;		//偏移
	switch (dir)
	{
	case up:
		fire->InitPos(coord.x + (TANK_WIDHT - FIRE_WIDHT) / 2, coord.y - FIRE_HEIGHT - skew,
			level, dir);
		break;
	case left:
		fire->InitPos(coord.x - FIRE_WIDHT - skew, coord.y + (TANK_HEIGHT - FIRE_HEIGHT) / 2,
			level, dir);
		break;
	case down:
		fire->InitPos(coord.x + (TANK_WIDHT - FIRE_WIDHT) / 2, coord.y + TANK_HEIGHT + skew,
			level, dir);
		break;
	case right:
		fire->InitPos(coord.x + TANK_WIDHT + skew, coord.y + (TANK_HEIGHT - FIRE_HEIGHT) / 2,
			level, dir);
		break;
	}
	fires.push_back(fire);
}

void CTank::MoveFire()
{
	for (int i = 0; i < fires.size(); i++)
	{
		fires[i]->Move();
	}
}

void CTank::Shoot(CBase * &item)
{
	//子弹碰撞
	ClearDieFire();
	for (int j = 0; j < fires.size(); j++)
	{
		fires[j]->ShootDie(item);
	}
	MoveFire();
}

void CTank::DrawFire(IplImage * backImg)
{
	for (int i = 0; i < fires.size(); i++)
	{
		CvPoint firePos = fires[i]->GetCurrPosition();
		if (!(firePos.x <= 0 || firePos.x >= BACKGROUND_WIDHT - FIRE_WIDHT
			|| firePos.y <= 0 || firePos.y >= BACKGROUND_HEIGHT - FIRE_HEIGHT))
		{
			fires[i]->Draw2Back(backImg);
		}
	}
}

void CTank::ClearDieFire()
{
	std::vector<CFire *>::iterator fire;
	for (fire = fires.begin(); fire != fires.end();)
	{
		if ((*fire)->IsDeath())
		{
			fire = fires.erase(fire);
		}
		else
			fire++;
	}
}

/*
void CTank::Crash(IplImage * backImg)
{
/ *
	if (this==item)return;

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
	bool hflag = (abs(fy1 + fy2 - ty1 - ty2) <= (th + fh));* /

	for (int i = 0; i < currImg[imgNo]->height; i++)
	{
		for (int j = 0; j < currImg[imgNo]->width; j++)
		{
			int valueB = CV_IMAGE_ELEM(currImg[imgNo], uchar, i, j * 3);
			int valueG = CV_IMAGE_ELEM(currImg[imgNo], uchar, i, j * 3 + 1);
			int valueR = CV_IMAGE_ELEM(currImg[imgNo], uchar, i, j * 3 + 2);

			int valueBackB = CV_IMAGE_ELEM(backImg, uchar, coord.y + i, (coord.x + j) * 3);
			int valueBackG = CV_IMAGE_ELEM(backImg, uchar, coord.y + i, (coord.x + j) * 3 + 1);
			int valueBackR = CV_IMAGE_ELEM(backImg, uchar, coord.y + i, (coord.x + j) * 3 + 2);
			if ((valueB != valueBackB)||(valueG != valueBackG)||(valueR != valueBackR))
			{
				cout << "YES"<<endl;
			}
		}
	}

	//if (wflag&&hflag)
	//{
	//	direction dirTemp = direction(item->GetDir());
	//	CvPoint changeCoor;
	//	while (dirTemp == direction(item->GetDir()))
	//	{			
	//		direction changeDir = direction(rand() % 4);
	//	item->setDir(changeDir);
	//	}
	//	switch (dir)
	//	{
	//	case up:
	//		changeCoor = cvPoint(fx2, fy1 + fh);
	//		break;
	//	case left:
	//		changeCoor = cvPoint(fx1 + fw, fy1 + fh);
	//		break;
	//	case down:
	//		changeCoor = cvPoint(fx2, fy1 - th);
	//		break;
	//	case right:
	//		changeCoor = cvPoint(fx1 - tw, fy2);
	//		break;
	//	}
	//	item->setCoord(changeCoor);
	//}
}*/