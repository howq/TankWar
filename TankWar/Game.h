#pragma once
class CGame
{
public:
	CGame();
	~CGame();

	void Start();
	void end();

	//��ʼ��BOSS
	void InitBoss(void);
	//��ʼ���з�̹��
	void InitTank();	
	//��ʼ���ҷ�̹��
	void InitMyTank(void);		
	//��ʼ��BOSS���ҷ�̹�ˣ��з�̹��Ⱥ



	//show
	void cvText(IplImage *showImg, char *text, CvPoint textPos);
	void setText(IplImage *showImg);

	void Init();

	//�����������
	void RandTool();
	//�������߲���ʼ��
	void CreatTool();
	//�ҷ�̹�˼������
	void GetTool();
	//�ж��Ƿ�������
	void judgeTool();

	//void ClearDieTool();

	//��BOSS,�ҷ�̹�ˣ��з�̹�ˣ����ߣ��ٻ��ɻ����ٻ���ǽ����elem Vector
	void InitItem();

	//̹�����
	void Shoot();
	//̹���ƶ����ɻ��ƶ�
	void Move(char key);
	//����ͼ��Ԫ��
	void Draw();
	//���������Ԫ��
	void ClearDie();
	//��Ϸ��������
	void Run();
	//�ж���Ϸ����
	void IsGameOver();

	//�ͷ�ͼƬ��Դ
	void ReleaseItem();
	//����new����
	void Delete();

	//�ٻ��ɻ�
	void CreatPlane(void);
	//��ʼ���ɻ�
	void InitPlaneImage(IplImage ** img);
	
	//�ٻ���ǽ
	void CreatWall(CvPoint position);
	//��ʼ����ǽ
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
	vector<CBase *> elem;		//���е�ͼƬԪ��
	vector<CTank *> tanks;
	vector<CTool *> tools;
	vector<CPlane *> planes;
	vector<CWall *> walls;

	const int tankCount = 20;	//�з�̹�˸���
	const int tankShow = 3;		//���Ƶз�̹����
	int tankDieCount;			//��ǰ���Ƶĵз�̹����
	bool isWin;					//����Ƿ�ʤ��
	bool gameOver;				//�Ƿ���Ϸ����
	bool gameStart;
};

