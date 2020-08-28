#include "../Database/Database.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    try {
        std::string str;
        Database db;
        setlocale(LC_ALL, ".ACP"); //vs9 bag
        if (argc < 2)
        {
            db.set.LoadFromFile();
            str = db.set.get_file_name();
        }
        else
        {
            str = argv[1];
            // .exm
        }
        
        std::ifstream ifs(str);
        if (!ifs.is_open()) {
            printf("Can not open file:%s\n", str.c_str());
            return -1;
        }

        if (db.LoadFromTextFile(ifs) < 1) return -2;

        std::ofstream ofs("db.rec", std::ios_base::binary);
        if (!ofs.is_open()) {
            return -3;
        }
        db.SaveToBinFile(ofs);
    }
    catch (const std::exception & ex) {
        std::cout << ex.what() << std::endl;
        system("pause");
    }
    return 0;
}
