#include "stdafx.h"

CGame::CGame()
{
	gameStart = true;
	tankDieCount = 0;
	isWin = false;
	gameOver = false;
	back = cvLoadImage("pics\\board.jpg");
	startImg = cvLoadImage("pics\\start.jpg");
	endImg[0] = cvLoadImage("pics\\end0.jpg");
	endImg[1] = cvLoadImage("pics\\end1.jpg");
	bossImg[0] = cvLoadImage("pics\\boss.jpg");
	wallImg[0] = cvLoadImage("pics\\wall.jpg");
	planeImg[0] = cvLoadImage("pics\\plane.jpg");

	char filename[50];
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(filename, 50, "pics\\tank%02d.jpg", i);
		tankImg[i] = cvLoadImage(filename);
		sprintf_s(filename, 50, "pics\\bomb%02d.jpg", i);
		fireImg[i] = cvLoadImage(filename);
	}
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(filename, 50, "pics\\tool%02d.jpg", i);
		toolImg[i] = cvLoadImage(filename);
	}
}

CGame::~CGame()
{
}

void CGame::Start()
{
	char key = 0;
//	gameStart = true;
	while (key!=13)
	{
		cvShowImage("TANKWAR", startImg);
		key = cvWaitKey(-1);
		//if (key == 27)
		//	break;
	}
	gameStart = false;
}

void CGame::end()
{
	tankDieCount = 0;
	myTank->SetDie(false);
	boss->SetDie(false);
	gameOver = false;
	char key = 0;
	while (key != 13)
	{
		if (isWin)
		{
			cvShowImage("TANKWAR", endImg[1]);
		} 
		else
		{
			cvShowImage("TANKWAR", endImg[0]);
		}
		key = cvWaitKey(-1);
	}
	Run();
}

void CGame::setText(IplImage *showImg)
{
	int lives = myTank->GetLive();
	int size = tanks.size();
	int lev0 = 0, lev1 = 0;
	for (int i = 0; i < tanks.size(); i++)
	{
		int count = tanks[i]->GetLevel();
		if (count == 0)
		{
			lev0++;
		}
		else
		{
			lev1++;
		}
	}
	char text[10];
	sprintf_s(text, "%d", lev0);
	cvText(showImg, text, cvPoint(670, 397));
	sprintf_s(text, "%d", lev1);
	cvText(showImg, text, cvPoint(670, 447));
	sprintf_s(text, "%d", lives);
	cvText(showImg, text, cvPoint(670, 497));
}

void CGame::cvText(IplImage *showImg,char *text,CvPoint textPos)
{
	CvFont font;
	double hscale = 1.0;
	double vscale = 1.0;
	int linewidth = 2;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX | CV_FONT_ITALIC, hscale, vscale, 0, linewidth);
	CvScalar textColor = cvScalar(0, 255, 255);
	cvPutText(showImg, text, textPos, &font, textColor);
}

void CGame::InitBoss()
{
	boss = new CMyTank;
	boss->SetCoord(cvPoint(0, 265));
	boss->Init(bossImg);
	boss->SetLive(1);
	boss->SetOrder(0);
	boss->SetDir(0);
}

void CGame::InitMyTank()
{
	myTank = new CMyTank;
	myTank->Init(tankImg);
	myTank->InitFireImage(fireImg);
}

void CGame::InitTank()
{
	tank = new CTank;
	tank->Init(tankImg);
	tank->InitFireImage(fireImg);
	tanks.push_back(tank);
}

void CGame::Init()
{
	InitBoss();
	InitMyTank();
	int i = 0;
	while (i < tankCount)
	{
		InitTank();
		i++;
	}
}

void CGame::CreatTool()
{
	tool = new CTool;
	tool->Init(toolImg);
	int currX = rand() % 460 + 90;
	int currY = rand() % 550;
	int levl = rand() % 4;
	tool->InitPos(currX,currY,levl);
	tools.push_back(tool);
}

void CGame::RandTool()
{
	if (0 == rand() % 300)
	{
		CreatTool();
	}
}

void CGame::GetTool()
{
	for (int i = 0; i < tools.size(); i++)
	{
		if (myTank->GetTool(tools[i]))
		{
			int levl = tools[i]->GetLevel();
			switch (levl)
			{
			case 0:myTank->AddLive(); break;
			case 1:if (myTank->GetLevel() < 2){ myTank->AddLevel();}break;
			case 2:CreatPlane();break;		//creat plane
			case 3:							//creat wall to protect boos
				CvPoint bossCoord = boss->GetCurrPosition();
				for (int i = 0; i < 4; i++)
				{
					CreatWall(cvPoint(WALL_WIDHT*i, bossCoord.y - WALL_HEIGHT));
					CreatWall(cvPoint(WALL_WIDHT*i, bossCoord.y + BOSS_HEIGHT));
					CreatWall(cvPoint(BOSS_WIDHT, bossCoord.y+WALL_HEIGHT*i));
				}
				break;		
			}
			tools[i]->SetDie(true);
		}
	}

}

void CGame::CreatPlane(void)
{
	CPlane * plane = new CPlane();
	plane->Init(planeImg);
	plane->InitFireImage(fireImg);
	planes.push_back(plane);
}

void CGame::CreatWall(CvPoint position)
{
	CWall * wall = new CWall();
	wall->Init(wallImg);
	wall->SetCoord(position);
	walls.push_back(wall);
}

void CGame::judgeTool()
{
	if (!gameOver)
	{
		RandTool();
		GetTool();
	}
}

void CGame::Shoot()
{
	if (tanks.size()<=tankShow)
	{
		for (int i = 2; i < tanks.size() + 2; i++)
		{
			elem[1]->Shoot(elem[i]);
			elem[i]->Shoot(elem[1]);
			elem[i]->Shoot(elem[0]);
			for (int j = 0; j < planes.size(); j++)
			{
				planes[j]->Shoot(elem[i]);
			}
			for (int j = 0; j < walls.size(); j++)
			{
				elem[i]->Shoot(elem[j]);
			}
		}
	} 
	else
	{
		for (int i = 2; i < tankShow + 2; i++)
		{
			elem[1]->Shoot(elem[i]);
			elem[i]->Shoot(elem[1]);
			elem[i]->Shoot(elem[0]);
			for (int j = 0; j < planes.size();j++)
			{
				planes[j]->Shoot(elem[i]);
			}
			for (int j = 0; j < walls.size(); j++)
			{
				elem[i]->Shoot(elem[j]);
			}
		}
	}
}

void CGame::Move(char key)
{
	myTank->SetKey(key);
	for (int i = 0; i < elem.size(); i++)			//mytank and tanks move
	{
		elem[i]->Move();
		elem[i]->MoveFire();
	}
}

void CGame::Draw()
{
	time_t stop = time(NULL);
	IplImage *showImage = NULL;
	//cvCopy(back, showImage);
	showImage = cvCloneImage(back);
	for (int i = 0; i < elem.size(); i++)			//mytank and tanks shoot
	{
		elem[i]->TimeEnd(stop);
		elem[i]->DrawFire(showImage);
		elem[i]->Draw2Back(showImage);
	}
	setText(showImage);
	cvShowImage("TANKWAR", showImage);
}

void CGame::InitItem()
{
	elem.clear();

	elem.insert(elem.begin(), planes.begin(), planes.end());
	elem.insert(elem.begin(), walls.begin(), walls.end());
	elem.insert(elem.begin(), tools.begin(), tools.end());
//	elem.insert(elem.begin(), tanks.begin(), tanks.end());

	if (tanks.size()>tankShow)
	{
		elem.insert(elem.begin(), tanks.begin(), tanks.begin() + tankShow);
	}
	else
	{
		elem.insert(elem.begin(), tanks.begin(), tanks.end());
	}

	elem.insert(elem.begin(), myTank);
	elem.insert(elem.begin(), boss);
}

void CGame::Run()
{
	cvNamedWindow("TANKWAR", CV_WINDOW_AUTOSIZE);
	Start();
	char key = 0;
	if (!gameStart)
	{
		while (1)
		{
			InitItem();
			IsGameOver();
			Shoot();
			Move(key);
			judgeTool();
			Draw();
			ClearDie();
			key = cvWaitKey(50);
		}
	}
}

void CGame::ClearDie()
{
	std::vector<CBase *>::iterator too;
	std::vector<CMyTank *>::iterator toMyTank;
	std::vector<CTank *>::iterator toTank;
	std::vector<CTool *>::iterator toTool;
	std::vector<CPlane *>::iterator toPlane;
	std::vector<CWall *>::iterator toWall;
	for (too = elem.begin(); too != elem.end();)
	{
	if ((*too)->IsDeath())
	{
	too = elem.erase(too);
	}
	else
	too++;
	}
	for (toTank = tanks.begin(); toTank != tanks.end();)
	{
		if ((*toTank)->IsDeath())
		{
			toTank = tanks.erase(toTank);
			tankDieCount++;
		}
		else
			toTank++;
	}
	for (toTool = tools.begin(); toTool != tools.end();)
	{
		if ((*toTool)->IsDeath())
		{
			toTool = tools.erase(toTool);
		}
		else
			toTool++;
	}
	for (toPlane = planes.begin(); toPlane != planes.end();)
	{
		if ((*toPlane)->IsDeath())
		{
			toPlane = planes.erase(toPlane);
		}
		else
			toPlane++;
	}
	for (toWall = walls.begin(); toWall != walls.end();)
	{
		if ((*toWall)->IsDeath())
		{
			toWall = walls.erase(toWall);
		}
		else
			toWall++;
	}

}

void CGame::IsGameOver()
{
	if (tankDieCount == tankCount)
	{
		gameOver = true;
		isWin = true;
	}
	if (elem[0]->IsDeath() || elem[1]->IsDeath())
	{
		gameOver = true;
		isWin = false;
	}
	if (gameOver)
	{
		end();
	}
}

void CGame::ReleaseItem()
{
	cvReleaseImage(&back);
	cvReleaseImage(&endImg[0]);
	cvReleaseImage(&endImg[1]);
	cvReleaseImage(&startImg);

	cvReleaseImage(&bossImg[1]);
	for (int i = 0; i < 8; i++)
	{
		cvReleaseImage(&tankImg[i]);
		cvReleaseImage(&fireImg[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		cvReleaseImage(&toolImg[i]);
	}
	cvReleaseImage(&planeImg[1]);
	cvReleaseImage(&wallImg[1]);
}

void CGame::Delete()
{
	delete myTank;
	delete tank;
	delete boss;
	delete tool;
	cvDestroyWindow("TANKWAR");
}
