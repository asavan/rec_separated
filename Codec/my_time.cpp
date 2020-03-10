#include "my_time.h"
#include <string>
#include <ctime>

class my_time_realization
{
    std::string _time;
    std::string _date;
    std::time_t ltime;
public:
    my_time_realization();
    time_t get_time_start() const { return ltime; }
    std::string get_time() const { return _time; }
    std::string get_date() const { return _date; }
};

my_time_realization::my_time_realization()
{
    ltime = std::time(nullptr);
    const int buf_size = 32;
    char buffer[buf_size];
    struct tm tM;
    localtime_s(&tM , &ltime);
    std::strftime(buffer, buf_size, "%H:%M:%S", &tM);
    _time = std::string(buffer);
    std::strftime(buffer, buf_size, "%d.%m.%Y", &tM);
    _date = std::string(buffer);
}

my_time::my_time() : realization(new my_time_realization())
{
}

my_time::~my_time() = default;

std::string my_time::get_time_differense() const
{
    time_t timeElapsed = std::time(nullptr) - realization->get_time_start();
    const int buf_size = 128;
    char c_str[buf_size];
    snprintf(c_str, buf_size, "%d:%.2d:%.2d", (int)(timeElapsed / 3600), (int)((timeElapsed / 60) % 60), (int)(timeElapsed % 60));
    std::string temp = c_str;
    return temp;
}

std::string my_time::get_time() const
{
    return realization->get_time();
}

std::string my_time::get_date() const
{
    return realization->get_date();
}
