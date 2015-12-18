#pragma once
class CBase
{
public:
	CBase();
	~CBase();
	virtual void Init(IplImage * *img);		//初始化
	virtual void Draw2Back(IplImage * backImg);		// 绘制
	virtual void Move(void){};		// 运动
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
	CvPoint coord;		//当前坐标
	CvPoint speed;		//速度
	IplImage * *currImg;		//当前图片
	int imgNo;			// 图片编号
	int level;			//tank's level
	int order;			//pics of tank's level
	bool isDead;		//死亡判断
	enum direction{left, up, down, right}dir;		//图片方向，子弹方向
	int live;			//生命值
	time_t start;
};

