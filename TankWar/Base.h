#pragma once
class CBase
{
public:
	CBase();
	~CBase();
	virtual void Init(IplImage * *img);		//��ʼ��
	virtual void Draw2Back(IplImage * backImg);		// ����
	virtual void Move(void){};		// �˶�
	void SetKey(int key){};			

	virtual void DrawFire(IplImage * backImg){};
	virtual void InitFireImage(IplImage ** img){};
	virtual void MoveFire(void){};		// 
	virtual void Shoot(CBase * &item){};

	inline void SetDie(bool die){ isDead = die; };
	inline void SetCoord(CvPoint m_coord){ coord = m_coord; };
	inline void SetDir(int m_dir){ dir = direction(m_dir); };
	inline void SetLive(int liv){ live = liv; };
	inline void SetLevel(int levl){ level = levl; };
	inline void SetOrder(int oder){ order = oder; };
	inline virtual bool IsDeath(){ return isDead; };
	virtual void TimeEnd(time_t stop){};

	CvPoint GetCurrPosition(){ return coord; };
	int GetLevel(){ return level; };
	int GetLive(){ return live; };
	int GetDir(){ return dir; };
	int GetCurrWidth(){ return this->currImg[imgNo]->width; };
	int GetCurrHeight(){ return this->currImg[imgNo]->height; };

protected:
	CvPoint coord;		//��ǰ����
	CvPoint speed;		//�ٶ�
	IplImage * *currImg;		//��ǰͼƬ
	int imgNo;			// ͼƬ���
	int level;			//tank's level
	int order;			//pics of tank's level
	bool isDead;		//�����ж�
	enum direction{left, up, down, right}dir;		//ͼƬ�����ӵ�����
	int live;			//����ֵ
	time_t start;
};

