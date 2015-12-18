#pragma once
#include "Base.h"
class CFire :
	public CBase
{
public:
	CFire();
	~CFire();
	virtual void Move(void);
	void ShootDie(CBase * &item);
	void InitPos(int currX, int currY, int levl,direction direc);		//
};

