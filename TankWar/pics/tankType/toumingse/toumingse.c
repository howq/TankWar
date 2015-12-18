#include "stdio.h"
#include "highgui.h"
#include "cv.h"
void main()
{
	IplImage *pBK;
	IplImage *pImg1;
	IplImage *pfish;
	CvMat bk;
	int j,i;
	pfish=cvLoadImage("yu.jpg",1); //����ͼƬ
	pBK=cvLoadImage("bk.jpg",1);
    cvGetSubRect( pBK, &bk , cvRect(200,100,pfish->width,pfish->height) );
	pImg1 = cvCreateImage(cvSize(pfish->width,pfish->height),IPL_DEPTH_8U,1);
	cvCvtColor(pfish,pImg1,CV_RGB2GRAY); //rgbת��Ϊ�Ҷ�ͼ
	for(j = 0;j< pImg1->height ; j++)
	{
		uchar* ptr = (uchar*)(pImg1->imageData+j*pImg1->widthStep);
		uchar* ptr1 = (uchar*)(pfish->imageData+j*pfish->widthStep);
		uchar* ptr2 = (uchar*)(bk.data.ptr+j*bk.step);
		for(i = 0;i < pImg1->width ; i++)
		{
			if(ptr[i] < 250)  //����ֵС��250�ı������� ����ʾ������ͼ�� ����ɫ���ֱ�ȥ�� 
			{
				ptr2[i*3] = ptr1[i*3];
				ptr2[i*3 + 1] = ptr1[i*3 + 1];
				ptr2[i*3 + 2] = ptr1[i*3 + 2];
			}
		}
	}
	cvNamedWindow("fish",1);
	cvShowImage("fish",pBK);
	cvWaitKey(0);
	cvReleaseImage( &pImg1);
}
