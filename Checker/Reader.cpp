#include "Reader.h"
#include "../Codec/codec.h"
#include "../Codec/my_time.h"
#include "../Utils/utils.h"
#include <fstream>
int Reader::LoadFromFile(std::istream& is)
{
    std::string(*load_string)(std::istream & is) = Codec::LoadStringFromFile;
    set.LoadFromFile(is, load_string);
    username = load_string(is);
    Time.data = load_string(is);
    Time.begin_time = load_string(is);
    Time.real_time = load_string(is);
    std::string size_temp = load_string(is);
    stats[3] = atoi(size_temp.c_str());
    for (int i = 0; i < stats[3]; ++i)
    {
        answer temp_answer;
        temp_answer.str = load_string(is);
        if (temp_answer.str.empty()) break;
        answers.push_back(temp_answer);
        ++(stats[temp_answer.mark]);
    }
    if (is) 
    {
        marks_begin = is.tellg();
    }
    else 
    {
        return 0;
    }
    if (stats[3] != answers.size()) {
        return 0;
    }
    std::string marks_str = load_string(is);
    if (!marks_str.empty())
    {
        for (int i = 0; i < stats[3]; ++i)
        {
            char c = marks_str[i];
            int mark = atoi(&c);
            set_mark(i, mark);
        }
        check_date = load_string(is);
        _is_first = false;
    }
    else {
        _is_first = true;
    }
    return stats[3];
}

std::string Reader::get_answer(size_t n) const
{
    return answers[n].str;
}

void Reader::set_mark(size_t n, int mark)
{
    int temp = answers[n].mark;
    answers[n].mark = mark;
    --(stats[temp]);
    ++(stats[mark]);
}
int Reader::get_mark(size_t n) const
{
    return answers[n].mark;
}

std::string Reader::get_username() const
{
    return username;
}

std::string Reader::get_check_date() const
{
    return check_date;
}

int Reader::size() const
{
    return size_as_int(answers);
}

bool Reader::is_first() const
{
    return _is_first;
}

std::string Stats::get_static() const
{
    return static_str;
}

Stats::Stats(Reader* read) : changed(false)
{
    r = read;
    save_string = SaveStringToTextFile;
}

void Stats::make_static()
{
    static_str.clear();
    static_str += "----Статистика----\r\n";
    static_str += "Пользователь: ";
    static_str += r->get_username();
    static_str += "\r\n";
    static_str += "Начал сдавать ";
    static_str += r->Time.data;
    static_str += " ";
    static_str += r->Time.begin_time;
    static_str += "\r\n";
    static_str += "Сдавал ";
    static_str += r->Time.real_time;
    static_str += "\r\n";
    static_str += "По базе '";
    static_str += r->set.get_name();
    static_str += "'\r\n";
    static_str += "\r\n";
    static_str += "\r\n";
    if (!r->is_first())
    {
        static_str += "Последняя проверка ";
        static_str += r->get_check_date();
    }
    static_str += "\r\n";

    //static_str+="\r\n";
}

std::string Stats::get_dynamic() const
{
    int mark_mass[6];
    for (int i = 0; i < 3; ++i)
    {
        mark_mass[i] = r->stats[i];
        mark_mass[i + 3] = mark_mass[i] * 100 / r->stats[3];
    }

    std::string dynamic_str;
    //dynamic_str = "\r\n";
    dynamic_str += "Непроверено\t";
    dynamic_str += IntToString(mark_mass[0], 2);
    dynamic_str += " (";
    dynamic_str += IntToString(mark_mass[3]);
    dynamic_str += "%)";
    dynamic_str += "\r\n";
    dynamic_str += "Правильно\t";
    dynamic_str += IntToString(mark_mass[1], 2);
    dynamic_str += " (";
    dynamic_str += IntToString(mark_mass[4]);
    dynamic_str += "%)";
    dynamic_str += "\r\n";
    dynamic_str += "Неправильно\t";
    dynamic_str += IntToString(mark_mass[2], 2);
    dynamic_str += " (";
    dynamic_str += IntToString(mark_mass[5]);
    dynamic_str += "%)";
    dynamic_str += "\r\n";
    return dynamic_str;
}

Stats::exit_mark Stats::make_exit_mark() const
{
    int percents_of_true = r->stats[1] * 100 / r->stats[3];
    if (percents_of_true <= 30)	return two;
    if (percents_of_true <= 60)	return three;
    if (percents_of_true <= 80)	return four;
    return five;
}

std::string Stats::make_string_from_mark(Stats::exit_mark m) const
{
    switch (m)
    {
    case Stats::one:
        break;
    case Stats::two:
        return "Не сдано";
    case Stats::three:
        return "Удовлетворительно";
    case Stats::four:
        return "Хорошо";
    case Stats::five:
        return "Отлично";

    }
    return "";
}

int Stats::MakeReport()
{
    if (!r) return -3; //no asoociate with reader;
    if (r->stats[0] != 0) return -1; //есть непроверенные
    std::ofstream out_txt((r->get_username() + '_' + r->set.get_ext() + ".txt").c_str());
    if (!out_txt.is_open()) return -2; // не открылся файл
    save_string(out_txt, get_static());


    int mark_mass[6];
    for (int i = 0; i < 3; ++i)
    {
        mark_mass[i] = r->stats[i];
        mark_mass[i + 3] = mark_mass[i] * 100 / r->stats[3];
    }


    std::string str = "Правильно ";
    str += IntToString(mark_mass[1], 2);
    str += " (";
    str += IntToString(mark_mass[4]);
    str += "%)";
    save_string(out_txt, str);

    str = "Неправильно ";
    str += IntToString(mark_mass[2], 2);
    str += " (";
    str += IntToString(mark_mass[5]);
    str += "%)";
    save_string(out_txt, str);

    str = "Оценка ";
    str += make_string_from_mark(make_exit_mark());
    str += "\n";
    save_string(out_txt, str);
    for (int i = 0; i < r->stats[3]; ++i)
    {
        save_string(out_txt, r->get_answer(i));
        str = "------Оценка-----\n";
        str += (r->get_mark(i) == Reader::true_mark) ? ("Правильно\n") : ("Неверно\n");
        save_string(out_txt, str);
    }
    return 0;
}

bool Reader::saveToFile(const std::string& fname)
{
    std::ofstream ofs(fname.c_str(), std::ios::out | std::ios::in | std::ios::ate | std::ios::binary);
    if (!ofs.is_open()) {
        return false;
    }
    ofs.seekp(marks_begin);
    // int j = ofs.tellp();
    std::string marks_str;
    marks_str.clear();
    for (int i = 0; i < stats[3]; ++i)
    {
        marks_str += IntToString(get_mark(i));
    }
    Codec::SaveStringToFile(ofs, marks_str);
    my_time exit_time;
    Codec::SaveStringToFile(ofs, exit_time.get_date());
    set_first(false);
    set_check_date(exit_time.get_date());
    return true;
}

void Stats::saveToFile(const std::string& fname)
{
    r->saveToFile(fname);

    make_static();
    MakeReport();
}

std::string Stats::getStatsString() const
{
    std::string str;
    str = get_static();
    str += "\r\n";
    str += get_dynamic();
    if (isAllCheked())
    {
        str += "\r\n\r\n";
        str += "Оценка: ";
        str += make_string_from_mark(make_exit_mark());
    }
    return str;
}

std::string Stats::getHeaderString() const
{
    std::string str;
    str += "Всего ";
    str += IntToString(r->size());
    str += "(";
    str += IntToString(r->stats[0]);
    str += "/";
    str += IntToString(r->stats[1]);
    str += "/";
    str += IntToString(r->stats[2]);
    str += ")";
    return str;
}
std::string Stats::getHeaderString2(int curr) const
{
    char tmp[128];
    sprintf_s(tmp, "Вопрос номер %d из %d.", curr + 1, r->stats[3]);
    std::string temp = tmp;
    return temp;
}
