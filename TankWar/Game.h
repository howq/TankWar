#pragma once
class CGame
{
public:
	CGame();
	~CGame();

	void Start();
	void end();

	//初始化BOSS
	void InitBoss(void);
	//初始化敌方坦克
	void InitTank();	
	//初始化我方坦克
	void InitMyTank(void);		
	//初始化BOSS，我方坦克，敌方坦克群



	//show
	void cvText(IplImage *showImg, char *text, CvPoint textPos);
	void setText(IplImage *showImg);

	void Init();

	//随机产生道具
	void RandTool();
	//产生道具并初始化
	void CreatTool();
	//我方坦克捡起道具
	void GetTool();
	//判断是否捡起道具
	void judgeTool();

	//void ClearDieTool();

	//将BOSS,我方坦克，敌方坦克，道具，召唤飞机，召唤城墙插入elem Vector
	void InitItem();

	//坦克射击
	void Shoot();
	//坦克移动，飞机移动
	void Move(char key);
	//绘制图像元素
	void Draw();
	//清楚死亡的元素
	void ClearDie();
	//游戏运行主体
	void Run();
	//判断游戏结束
	void IsGameOver();

	//释放图片资源
	void ReleaseItem();
	//销毁new对象
	void Delete();

	//召唤飞机
	void CreatPlane(void);
	//初始化飞机
	void InitPlaneImage(IplImage ** img);
	
	//召唤城墙
	void CreatWall(CvPoint position);
	//初始化城墙
	void InitWallImage(IplImage ** img);

private:
	IplImage *back;
	IplImage *startImg;
	IplImage *endImg[2];
	IplImage *bossImg[1];
	IplImage *tankImg[8];
	IplImage *fireImg[8];
	IplImage *toolImg[4];
	IplImage *planeImg[1];
	IplImage *wallImg[1];

	CTank *tank;
	CTool *tool;

	CMyTank *boss;
	CMyTank *myTank;
	vector<CBase *> elem;		//所有的图片元素
	vector<CTank *> tanks;
	vector<CTool *> tools;
	vector<CPlane *> planes;
	vector<CWall *> walls;

	const int tankCount = 20;	//敌方坦克个数
	const int tankShow = 3;		//绘制敌方坦克数
	int tankDieCount;			//当前绘制的敌方坦克数
	bool isWin;					//玩家是否胜利
	bool gameOver;				//是否游戏结束
	bool gameStart;
};

