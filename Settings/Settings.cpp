#include "Settings.h"
#include <fstream>

static std::string loadFromTextFile(std::istream& is)
{
    std::string temp;
    getline(is, temp);
    return temp;
}

void Settings::LoadFromFile()
{
    //	setlocale( LC_ALL, ".ACP" ); //vs9 bag
    std::ifstream ifs("settings.txt");
    if (!ifs.is_open()) return;
    LoadFromFile(ifs, loadFromTextFile);
}

std::string Settings::get_name() const
{
    return names[0];
}

std::string Settings::get_file_name() const
{
    return names[2];
}

std::string Settings::get_ext() const
{
    return names[1];
}

std::string Settings::get_names(size_t i) const
{
    return names[i];
}

void  Settings::set_names(size_t i, const  std::string& str)
{
    names[i] = str;
}


void Settings::SaveToFile(std::ostream& os, void (*save_string)(std::ostream& os, const std::string& s)) const
{
    for (int i = 0; i < number_of_fields; ++i)
    {
        save_string(os, get_names(i));
    }
}

void Settings::LoadFromFile(std::istream& is, std::string(*load_string)(std::istream& is))
{
    for (int i = 0; i < number_of_fields; ++i)
    {
        names[i] = load_string(is);
    }
}
