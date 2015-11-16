#pragma once
#include <string>

class Settings
{

	static const int number_of_fields = 3;
public:
	

	//Settings();
	void LoadFromFile();
	std::string get_name() const;
	std::string get_file_name() const;	
	std::string get_ext() const;
	void SaveToFile(std::ostream &os, void (*save_string)(std::ostream &os, const std::string &s)) const;
	void LoadFromFile(std::istream &is,  std::string (*load_string)(std::istream &is));

private:
	std::string get_names(size_t i) const;
	void set_names(size_t i, const std::string &str);

	std::string names[number_of_fields];//name, rasshir, file_name;

};