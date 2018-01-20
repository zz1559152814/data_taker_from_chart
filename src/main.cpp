#include "./includes.h"
#include "math.h"

using namespace std;
using namespace cv;  

int main( int argc, char** argv )
{	
	ProcessClass myobject("../photo.png");
	myobject.Rotate(1, true);
	myobject.CutOff(70,2,353,205);
	myobject.ToBlack(50);
	myobject.Calculate(3,0.05);
}
