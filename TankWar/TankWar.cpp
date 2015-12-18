// TankWar.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

     
int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));			//随机数种子的设置
	CGame *game = new CGame;
	game->Init();				//初始化
	game->Run();				//运动起来
	game->ReleaseItem();		//释放资源
	game->Delete();

	return 0;
}

