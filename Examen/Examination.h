#pragma once
#include "../Database/Database.h"
#include <memory>

class my_time;
class Examination {
public:
    Examination();
    ~Examination();
    const Settings& get_set() const { return db.set; };
    void startExamen();
    void MakeAnswerOrder();
    int size() const;
    std::string get_question(int n) const;
    std::string get_answer(int n) const;
    void set_answer(int n, const std::string& s);
    bool LoadFromFile(std::istream& is);
    void SaveToFile(std::ostream& os, const char* username) const;
    std::string get_time_differense() const;

private:
    Database db;
    struct Answer {

        Adress adress; //����� � ����
        std::string str; // �����
        Answer() :adress(0, 0) { }
    };
    std::string name;
    std::vector<Answer> answers;
    std::unique_ptr<my_time> _time;
    Examination(const Examination&) = delete;
    Examination& operator=(const Examination&) = delete;
};
// inline std::string get_time (time_t time);
