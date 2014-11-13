#include "my_time.h"
#include <string>
#include <ctime>

class my_time_realization
{
	struct tm _tm;
	std::string _time;
	std::string _date;
	time_t ltime;
public:
	my_time_realization();
	time_t get_time_start() const {return ltime;} 
	std::string get_time(void) const {return _time;}
	std::string get_date(void) const {return _date;}
};

my_time_realization::my_time_realization()
{
	time(&ltime);
	localtime_s(&_tm, &ltime);
	std::string temp = ctime(&ltime);
	_time = temp.substr(10,9);
	char c_str[16];
	sprintf_s( c_str, "%.2d.%.2d.%.4d", _tm.tm_mday, _tm.tm_mon +1, _tm.tm_year +1900 );
	_date = c_str;

}

my_time::my_time()
{
	realization = new my_time_realization();
}

my_time::~my_time()
{
	delete realization;
}

std::string my_time::get_time_differense() const 
{
	time_t timeElapsed = time(0)-realization->get_time_start();	
	char c_str[128];
	sprintf_s( c_str, "%d:%.2d:%.2d", (int)(timeElapsed/3600), (int)((timeElapsed/60)%60), (int)(timeElapsed%60) );
	std::string temp = c_str;
	return temp;
} 

std::string my_time::get_time(void) const
{
	return realization->get_time();
}
std::string my_time::get_date(void) const
{
	return realization->get_date();
}

