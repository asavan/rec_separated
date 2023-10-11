#include "Database.h"
#include "../Codec/codec.h"
#include "../Utils/utils.h"

#include <iostream>
#include <stdexcept>


namespace {
    inline bool empty_symbol(char c)
    {
        return (c == '\n' || c == ' ' || c == '\t');
    }
    void ErrorInZone(int n)
    {
        std::string str("zone ");
        str += IntToString(n + 1);
        str += " is empty";
        throw std::runtime_error(str);
    }
}

size_t q_zone::LoadZoneText(std::istream& is, int pro)
{
    questions.clear();
    z_property = pro;
    while (is)
    {
        std::string str;
        char c = 0;
        bool bCR = false;
        while (is >> c)
        {
            if (str.empty())
            {
                if (c == '@') { return questions.size(); }
                if (empty_symbol(c))continue;
            }
            if (c == '\n')
            {
                //if (str.size()==0) continue; //empty enter break
                if (bCR) { break; }
                else { bCR = true; }
            }
            else
            {
                if (bCR)
                {
                    str.push_back('\r');
                    str.push_back('\n');
                    bCR = false;
                    // if(empty_symbol (c) ) continue;
                }
                str.push_back(c);
            }
        }
        if (!str.empty())
        {
            questions.push_back(str);
        }
    }
    return questions.size();

}


q_zone::q_zone(std::istream& is, int pro)
{
    LoadZoneText(is, pro);
}

size_t Database::LoadFromTextFile(std::istream& is)
{
    is.unsetf(std::ios_base::skipws);
    zones.clear();
    int count = 0;
    while (is && !is.eof())
    {
        q_zone z_temp(is, count);
        if (z_temp.size() == 0)
        {
            ErrorInZone(size());
        }
        zones.push_back(z_temp);
        char c;
        is >> c;
        if (is)
        {
            switch (c)
            {
            case '\n':
                count = 0;
                break;
            default:
                count = atoi(&c);
                is.get();
                break;
            }
        }
    }
    return zones.size();
}
/*
size_t Database::LoadFromFile( std::istream  &is)
{
    if (is.flags()&std::ios_base::binary)
        return LoadFromBinFile(is);

    else
        return LoadFromTextFile(is);

}
*/
const char sign[] = "\x00\xFFRECDB";

/*
size_t q_zone::LoadFromBinFile( std::istream & is) {
    while( is ) {
        std::string str = Codec::LoadStringFromFile( is );
        if( str!="" ) {
            questions.push_back( str );
        }
    }
    return questions.size();
}*/
size_t Database::LoadFromBinFile(std::istream& is)
{
    char this_sign[sizeof(sign)];
    is.read(this_sign, sizeof(sign));
    for (unsigned int i = 0; i < sizeof(sign); i++)
    {
        if (this_sign[i] != sign[i])
        {
            return 0;
        }
    }

    set.LoadFromFile(is, Codec::LoadStringFromFile);

    while (!is.eof() && is)
    {
        q_zone temp_zone;
        if (temp_zone.LoadZoneBin(is) < 1) break;
        zones.push_back(temp_zone);
    }
    return size();
}


void q_zone::SaveToBinFile(std::ostream& os) const
{
    int size = size_as_int(questions);
    os.write((char*)&z_property, sizeof(int));

    os.write((char*)&size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        Codec::SaveStringToFile(os, questions[i]);
    }
}

size_t q_zone::LoadZoneBin(std::istream& is)
{
    int size = 0;
    is.read((char*)&z_property, sizeof(int));
    is.read((char*)&size, sizeof(int));

    for (int i = 0; i < size; i++)
    {
        std::string str = Codec::LoadStringFromFile(is);
        if (!str.empty())
        {
            questions.push_back(str);
        }
    }
    return questions.size();
}

void Database::SaveToBinFile(std::ostream& os) const
{
    os.write(sign, sizeof(sign));
    set.SaveToFile(os, Codec::SaveStringToFile);
    for (int i = 0; i < size(); ++i)
    {
        zones[i].SaveToBinFile(os);
    }
}

int Database::size() const
{
    return size_as_int(zones);
}

size_t q_zone::difficult() const
{
    return z_property;
}

q_zone::q_zone() : z_property(0)
{
}

void q_zone::push_back(std::string q)
{
    questions.push_back(q);
}

int q_zone::size() const
{
    return size_as_int(questions);
}

std::string q_zone::operator[](int n) const
{
    return questions[n];
}
