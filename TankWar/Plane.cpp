#include "stdafx.h"
#include "Plane.h"


CPlane::CPlane()
{
	live = 1;
	order = 4;
	level = 0;
	dir = direction(0);
	isDead = false;
	coord = cvPoint((BACKGROUND_WIDHT - PLANE_WIDHT) / 2, 0);
	speed.y = PLANESPEEDY;
}

CPlane::~CPlane()
{
}

void CPlane::Move()
{
	coord.y += speed.y;

	if (coord.y == BACKGROUND_HEIGHT - PLANE_HEIGHT - speed.y)
	{
		coord.y = BACKGROUND_HEIGHT - PLANE_HEIGHT;
		isDead = true;
	}
	if (rand()%8==0)
	{
		CreatFire();
	}
}

void CPlane::InitFireImage(IplImage ** img)
{
	fireImg = img;
}

void CPlane::CreatFire()
{
	CFire * fire = new CFire();
	fire->Init(fireImg);
	direction dire = direction(rand() % 4);
	int skewX = rand() % PLANE_WIDHT;
	int skewY = rand() % PLANE_HEIGHT;
	fire->InitPos(coord.x + skewX, coord.y + skewY, 1, dire);
	fires.push_back(fire);
}

void CPlane::MoveFire()
{
	for (int i = 0; i < fires.size(); i++)
	{
		fires[i]->Move();
	}
}

void CPlane::Shoot(CBase * &item)
{
	//×Óµ¯Åö×²
	ClearDieFire();
	for (int j = 0; j < fires.size(); j++)
	{
		fires[j]->ShootDie(item);
	}
	MoveFire();
}

void CPlane::DrawFire(IplImage * backImg)
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

void CPlane::ClearDieFire()
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