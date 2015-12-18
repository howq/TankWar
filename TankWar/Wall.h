#pragma once
#include "Base.h"
class CWall :
	public CBase
{
public:
	CWall();
	~CWall();
	virtual void TimeEnd(time_t stop);

};

