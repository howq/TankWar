#include "stdafx.h"

CBase::CBase()
{

}

CBase::~CBase()
{
}

// 绘制
void CBase::Draw2Back(IplImage * backImg)
{
	if (isDead){ return; }
	if (level < 0)level = 0;
	imgNo = level * order + dir;

	IplImage *pBK = backImg;
//	IplImage *pItem = currImg[imgNo];
	IplImage *pItem = NULL;
	IplImage *pImg1 = NULL;
	pItem = cvCloneImage(currImg[imgNo]);
	CvMat bk;
	int j, i;
	cvGetSubRect(pBK, &bk, cvRect(coord.x, coord.y, pItem->width, pItem->height));
	pImg1 = cvCreateImage(cvSize(pItem->width, pItem->height), IPL_DEPTH_8U, 1);
	cvCvtColor(pItem, pImg1, CV_RGB2GRAY); //rgb转换为灰度图
	for (j = 0; j < pImg1->height; j++)
	{
		uchar* ptr = (uchar*)(pImg1->imageData + j*pImg1->widthStep);
		uchar* ptr1 = (uchar*)(pItem->imageData + j*pItem->widthStep);
		uchar* ptr2 = (uchar*)(bk.data.ptr + j*bk.step);
		for (i = 0; i < pImg1->width; i++)
		{
			if (ptr[i] < 250)  //像素值小于250的保留下来 并显示到背景图上 即白色部分被去除 
			{
				ptr2[i * 3] = ptr1[i * 3];
				ptr2[i * 3 + 1] = ptr1[i * 3 + 1];
				ptr2[i * 3 + 2] = ptr1[i * 3 + 2];
			}
		}
	}
	//cvNamedWindow("pItem", 1);
	//cvShowImage("pItem", pBK);
	//cvWaitKey(0);
	//cvReleaseImage(&pImg1);

}

void CBase::Init(IplImage * *img)
{
	currImg = img;
}
