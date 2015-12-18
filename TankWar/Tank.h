#pragma once
#include<vector>
#include "Base.h"
#include "Fire.h"
using namespace std;

class CTank :
	public CBase
{
public:
	CTank();
	~CTank();

	virtual void Move(void);
	void CreatFire(void);
	void ClearDieFire();
	virtual void Shoot(CBase * &item);
	virtual void InitFireImage(IplImage ** img);
	virtual void DrawFire(IplImage * backImg);
	virtual void MoveFire(void);		// �˶�
	//virtual void Crash(IplImage * backImg);
protected:
	IplImage ** fireImg;
	vector<CFire *> fires;	// ���û�ҩ������
};

