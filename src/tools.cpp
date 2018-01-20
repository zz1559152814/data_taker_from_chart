#include "includes.h"
using namespace std;
using namespace cv;  


string Tools::Char_To_String(char *a)
{
  string b = a;
  return b;
}

string Tools::ConstChar_To_String(const char *a)
{
	string b = a;
	return b;
}

const char* Tools::String_To_ConstChar(string a)
{
	const char *b = a.data();
	return b;
}

string Tools::int_to_string(int a){
	ostringstream output;
	output<<a;
	string str = output.str();
	return str;
}
string Tools::G_filename(string proname)
{
  	time_t currentTime;
  	struct tm *localTime;
  	time( &currentTime );                   // Get the current time
	localTime = localtime( &currentTime );
	int Day    = localTime->tm_mday;
  	int Month  = localTime->tm_mon + 1;
  	int Hour   = localTime->tm_hour;
  	int Min    = localTime->tm_min;
  	int Sec    = localTime->tm_sec;
  	string filename = proname;
  	string zero = "0";
  	if(Month<10)
  		filename.append(zero);
  	filename.append(int_to_string(Month));	
  	if(Day<10)
  		filename.append(zero);	
  	filename.append(int_to_string(Day));	
  	if(Hour<10)
  		filename.append(zero);	
  	filename.append(int_to_string(Hour));	
  	if(Min<10)
  		filename.append(zero);	
  	filename.append(int_to_string(Min));	
  	if(Sec<10)
  		filename.append(zero);		
  	filename.append(int_to_string(Sec));	
  	filename.append(".png");	
  	return filename;
}