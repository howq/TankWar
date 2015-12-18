#pragma once
#include "Base.h"
#include "Plane.h"
#include "Wall.h"
class CTool :
	public CBase
{
public:
	CTool();
	~CTool();
	void InitPos(int currX, int currY, int levl);
	virtual void TimeEnd(time_t stop);
};

