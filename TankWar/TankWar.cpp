// TankWar.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

     
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));			//��������ӵ�����
	CGame *game = new CGame;
	game->Init();				//��ʼ��
	game->Run();				//�˶�����
	game->ReleaseItem();		//�ͷ���Դ
	game->Delete();

	return 0;
}

