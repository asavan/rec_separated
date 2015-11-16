#pragma once
#include <string>
class my_time_realization;
class my_time
{
	my_time_realization* realization;
	
	//;
	my_time(const my_time&);
public:
	~my_time();
	my_time();
	std::string get_time_differense() const;
	std::string get_time(void) const;
	std::string get_date(void)const;
};
