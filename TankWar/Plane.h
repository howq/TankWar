#pragma once
#include "Base.h"
class CPlane :
	public CBase
{
public:
	CPlane();
	~CPlane();
	void CreatFire(void);
	void ClearDieFire();
	virtual void Shoot(CBase * &item);
	virtual void InitFireImage(IplImage ** img);
	virtual void DrawFire(IplImage * backImg);
	virtual void MoveFire(void);		// 运动
	virtual void Move(void);		// 运动
private:
	IplImage ** fireImg;
	vector<CFire *> fires;	// 放置火药的容器
};

