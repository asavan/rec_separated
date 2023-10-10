#include "my_time.h"
#include <string>
#include <chrono>
#include <format>

class my_time_realization
{
    std::string _time;
    std::string _date;
    std::chrono::time_point<std::chrono::steady_clock> _ltime;
public:
    my_time_realization();
    std::chrono::time_point<std::chrono::steady_clock> get_time_start() const { return _ltime; }
    std::string get_time() const { return _time; }
    std::string get_date() const { return _date; }
};

my_time_realization::my_time_realization()
{
    auto const time = std::chrono::current_zone()
        ->to_local(std::chrono::system_clock::now());
    _ltime = std::chrono::steady_clock::now();
    _time = std::format("{:%T}", time);
    _date = std::format("{:%d.%m.%Y}", time);
}

my_time::my_time() : realization(new my_time_realization())
{
}

my_time::~my_time() = default;

std::string my_time::get_time_differense() const
{
    auto timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - realization->get_time_start());
    return std::format("{:%T}", timeElapsed);
}

std::string my_time::get_time() const
{
    return realization->get_time();
}

std::string my_time::get_date() const
{
    return realization->get_date();
}
