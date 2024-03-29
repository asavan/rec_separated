#include "codec.h"
#include "../Utils/utils.h"

#include <vector>
#include <iostream>

namespace Codec {

    const char def_char = '\xC6';

    std::vector<char> Encode(const std::string& str) {
        size_t l = str.size();
        std::vector<char> res(l);
        if (l) {
            res[0] = str[0] + def_char;
        }
        for (size_t i = 1; i < l; i++) {
            res[i] = res[i - 1] + str[i];
        }
        return res;
    }

    std::string Decode(const std::vector<char>& str)
    {
        int l = size_as_int(str);
        std::string res;
        res.resize(l);
        if (l > 1)
        {
            for (int i = l - 1; i > 0; i--)
            {
                res[i] = str[i] - str[i - 1];
            }
        }
        if (l)
        {
            res[0] = str[0] - def_char;
        }
        return res;
    }

    void SaveStringToFile(std::ostream& os, const std::string& str_in)
    {
        std::vector<char> str_enc = Encode(str_in);
        int l = size_as_int(str_enc);
        os.write((char*)&l, sizeof(int));
        for (char t : str_enc) {
            os << t;
        }
    }

    std::string LoadStringFromFile(std::istream& is) {
        int l;
        is.read((char*)&l, sizeof(int));
        if (!is) { return ""; }
        std::vector<char> str_enc;

        for (int i = 0; i < l; i++)
        {
            char t;
            is.get(t);
            if (is.eof()) { break; }
            str_enc.push_back(t);
        }
        return Decode(str_enc);
    }

} // namespace Codec
void SaveStringToTextFile(std::ostream& os, const std::string& str)
{
    os << str << std::endl;
}

std::string IntToString(int in, int field_size)
{
    std::string s = std::to_string(in);
    if (size_as_int(s) < field_size) {
        s.insert(s.begin(), field_size - s.size(), ' ');
    }
    return s;
}
