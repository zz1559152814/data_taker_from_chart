
class ProcessClass
{
public:
	ProcessClass(const char* filename);
	~ProcessClass(void); 
	int Rotate(int angle,bool clockwise);
	int CutOff(int x_begin,int y_begin,int x_area,int y_area);
	int ToBlack(int pos);
	int GetData(void);
	int Calculate(double x_value, double y_value);
private:
	IplImage* _src;
	IplImage* _afterRotate;
	IplImage* _afterCut;
	IplImage* _afterBinary;
	int _x_begin,_y_begin,_x_area,_y_area;
	int ShowImage(const char* name,IplImage* image);
};