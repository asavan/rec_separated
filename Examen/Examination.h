#pragma once
#include "../Database/Database.h"

class my_time;
class Examination {
	Database db;
	struct Answer {
		
		Adress adress ; //адрес в базе
		std::string str; // ответ
		Answer():adress(0,0){ }
	};
	std::string name;
	std::vector<Answer> answers;
	my_time *_time;
	Examination(const Examination&);
	void setTime(my_time *t);
public:
	Examination();
	~Examination();
	const Settings& get_set()const {return db.set;};
	void startExamen();
	void MakeAnswerOrder(void);
	size_t size() const;
	std::string get_question( size_t n )const;
	std::string get_answer( size_t n ) const;
	void set_answer( size_t n, std::string s );
	bool LoadFromFile( std::istream &is );	
	void SaveToFile( std::ostream &os, const char * username ) const;	
	std::string get_time_differense() const;
};
// inline std::string get_time (time_t time);