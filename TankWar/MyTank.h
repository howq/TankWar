#pragma once
#include "Tank.h"
#include "Tool.h"
class CMyTank :
	public CTank
{
public:
	CMyTank();
	~CMyTank();
	virtual void Move();
//	void Draw2Back(IplImage * backImg);
	void SetKey(char keyboard){ key = keyboard; };
	bool GetTool(CTool * &tool);
	void AddLive(){ live++; }
	void AddLevel(){ level++; }
private:
	char key;
};

