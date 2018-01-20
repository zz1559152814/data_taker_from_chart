#include "./includes.h"
using namespace std;
using namespace cv;  	

ProcessClass::ProcessClass(const char* filename)
{
	_src	= cvLoadImage(filename,1);
	ShowImage("src",_src);
}

ProcessClass::~ProcessClass(void)
{
	cvReleaseImage(&_src);  
	cvReleaseImage(&_afterRotate);  
	cvReleaseImage(&_afterCut);  
	cvReleaseImage(&_afterBinary);  
}
int ProcessClass::Rotate(int angle,bool clockwise)
{	
	angle = abs(angle) % 180;  
    if (angle > 90)  
    {  
        angle = 90 - (angle % 90);  
    }  
    int width =  
        (double)(_src->height * sin(angle * CV_PI / 180.0)) +  
        (double)(_src->width * cos(angle * CV_PI / 180.0 )) + 1;  
    int height =  
        (double)(_src->height * cos(angle * CV_PI / 180.0)) +  
        (double)(_src->width * sin(angle * CV_PI / 180.0 )) + 1;  
    int tempLength = sqrt((double)_src->width * _src->width + _src->height * _src->height) + 10;  
    int tempX = (tempLength + 1) / 2 - _src->width / 2;  
    int tempY = (tempLength + 1) / 2 - _src->height / 2;  
    int flag = -1;  
  
    _afterRotate = cvCreateImage(cvSize(width, height), _src->depth, _src->nChannels);  
    cvZero(_afterRotate);  
    IplImage* temp = cvCreateImage(cvSize(tempLength, tempLength), _src->depth, _src->nChannels);  
    cvZero(temp);  
  
    cvSetImageROI(temp, cvRect(tempX, tempY, _src->width, _src->height));  
    cvCopy(_src, temp, NULL);  
    cvResetImageROI(temp);  
  
    if (clockwise)  
        flag = 1;  
  
    float m[6];  
    int w = temp->width;  
    int h = temp->height;  
    m[0] = (float) cos(flag * angle * CV_PI / 180.);  
    m[1] = (float) sin(flag * angle * CV_PI / 180.);  
    m[3] = -m[1];  
    m[4] = m[0];  
    // 将旋转中心移至图像中间  
    m[2] = w * 0.5f;  
    m[5] = h * 0.5f;  
    //  
    CvMat M = cvMat(2, 3, CV_32F, m);  
    cvGetQuadrangleSubPix(temp, _afterRotate, &M);  
    cvReleaseImage(&temp);  
    ShowImage("afterRotate",_afterRotate);
    cvSaveImage("../afterRotate.jpg",_afterRotate);
}

int ProcessClass::CutOff(int x_begin,int y_begin,int x_area,int y_area)
{
	_x_begin = x_begin;
	_y_begin = y_begin;
	_x_area	 = x_area;
	_y_area  = y_area;
	CvSize size;
	size= cvSize(x_area,y_area);//区域大小
	cvSetImageROI(_afterRotate,cvRect(x_begin,y_begin,x_area,y_area));//设置源图像ROI
	_afterCut = cvCreateImage(size,_src->depth,_src->nChannels);//创建目标图像
	cvCopy(_afterRotate,_afterCut); //复制图像
	cvResetImageROI(_afterCut);//源图像用完后，清空ROI
	ShowImage("afterCut",_afterCut);
	cvSaveImage("../afterCut.jpg",_afterCut);//保存目标图像	
}

int ProcessClass::ToBlack(int pos)
{
	IplImage* g_pGrayImage;
	g_pGrayImage =  cvCreateImage(cvGetSize(_afterCut), IPL_DEPTH_8U, 1);  
    cvCvtColor(_afterCut, g_pGrayImage, CV_BGR2GRAY);  
    // 创建二值图  
    _afterBinary = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1); 
    cvThreshold(g_pGrayImage, _afterBinary, pos, 255, CV_THRESH_BINARY); 
	for(int i=_afterBinary->height-1;i>_afterBinary->height-5;i--)		
		for(int j=0;j<_afterBinary->width;j++)
		{
			CvScalar cs = cvGet2D(_afterBinary, 10, 0);
            cvSet2D(_afterBinary, i, j, cs);
		}
    ShowImage("BlackImg",_afterBinary);
	cvSaveImage("../afterBinary.jpg",_afterBinary);
}

int ProcessClass::ShowImage(const char* name,IplImage* image)
{
	cvNamedWindow(name,1);
 	cvShowImage(name,image);
 	cvWaitKey(0);        
 	cvDestroyWindow(name);
}

//	begin:截取的起始点
//	area :截取的大小
//	value:实际的坐标取值范围
int ProcessClass::Calculate(double x_value, double y_value)
{
	float array[_x_area];
	int y_s,in;
	int count;
    for(int j=0;j<_afterBinary->width;j++)
	{
		y_s = 0;
		in = 0;
		for(int i=0;i<_afterBinary->height;i++)
		{
			count = cvGet2D(_afterBinary,i,j).val[0];
			if(count==0)
			{
				in += 1;
				y_s += i;
			}
		}
		if(in!=0)
			array[j] = y_s/in;
		else
			array[j] = 0;
	}

	double x_per = x_value/(double)_afterRotate->width;
	double y_per = y_value/(double)_afterRotate->height;
	double x,y;
	char filename[] = "../data.txt"; 
	ofstream fout(filename);
	for(int i=0; i<_afterRotate->width; i++)
	{
		if(i<_x_begin||i>(_x_begin+_x_area)||array[i-_x_begin]==0)
		{
			x = i*x_per;
			fout<<x<<": "<<i<<": 0"<<endl;
		}
		else
		{
			x = i*x_per;
			y = (_afterRotate->height-(array[i-_x_begin]+_y_begin))*y_per;
			fout<<x<<": "<<i<<": "<<y<<endl;
		}
	}
}