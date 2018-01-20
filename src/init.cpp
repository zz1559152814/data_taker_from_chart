#include "includes.h"

using namespace std;
using namespace cv;  

     
int Init::take_photo(){
	Tools tool;
	VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    for(;;)
    {
        cap >> src; // get a new frame from camera
        imshow("video", src);
        if(waitKey(30) >= 0){
	  		vector<int> compression_params;
    		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    		compression_params.push_back(9);
			string filename = string("/home/dream/codes/gojuon/database/").append(tool.G_filename("src"));
	  	    const char* c_filename= tool.String_To_ConstChar(filename);
	  	    imwrite(c_filename,src,compression_params);
	  	    break;	
        } 
    }
    return 0;
}

int Init::graying(void){
	Tools tool;
	Mat grey;
	cvtColor(src,grey,CV_BGR2GRAY);
	grey.copyTo(src);
	grey.release();
	string filename = string("/home/dream/codes/gojuon/database/").append(tool.G_filename("gray"));
	vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
	const char* c_filename= tool.String_To_ConstChar(filename);
	imwrite(c_filename,src,compression_params);
	return 0;
}