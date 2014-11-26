#include<vector>
#include "../Settings/Settings.h"

class Stats;
class Reader
{
	struct answer
	{ 
		std::string str;
		int mark;
		answer(void) :mark(unset){}
	};
	std::vector<answer> answers; 
	std::string username;
	std::string check_date;

	struct _Time{
		std::string data;
		std::string begin_time;
		std::string real_time;
	};
	bool _is_first;
	long marks_begin;	
	Settings set;
	_Time Time;
	int stats[4]; //unset , true, false, all;
public:
	friend Stats; // fix this
	
	bool is_first() const;
	void set_first(bool i) {_is_first = i;}
	bool saveToFile(std::string filename);
	
	enum marks { unset, true_mark, false_mark};
	int LoadFromFile(std::istream &is);
	std::string get_answer( size_t n ) const;
	int get_mark( size_t n ) const;
	void set_mark(size_t n, int mark);
	std::string get_username() const; 
	void set_check_date(const std::string & str) {check_date = str;}
	std::string get_check_date() const;
	size_t size() const;
	
};

class Stats
{		
	
public:
	
	enum exit_mark{ one , two, three, four, five};
	exit_mark make_exit_mark() const;
	//exit_mark mark;0

	bool is_changed() const {return changed;}
	void set_changed(bool ch) {changed = ch;}
	std::string get_static() const;
	std::string get_dynamic()const;
	void make_static();
	int MakeReport();
	void saveToFile(std::string filename);
	bool isAllCheked() const {return (r->stats[0] == 0); }
	std::string getStatsString() const;
	std::string getHeaderString() const;
	std::string getHeaderString2(int curr) const;
	

	explicit Stats(Reader * read);

private:
	void (*save_string)(std::ostream &os, const std::string &str);
	std::string make_string_from_mark(exit_mark m) const;

	std::string static_str;
	bool changed;
	Reader * r;
};

