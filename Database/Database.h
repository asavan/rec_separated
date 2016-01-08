#pragma once
#include "../Settings/Settings.h"

#include <vector>
#include <string>
#include <iostream>


class Adress
{
    size_t i;
	size_t j; 
public:	
	Adress(size_t _j, size_t _i) : i(_i), j(_j) {}
	size_t getZoneNumber() const {return j;}
	size_t getQuestionNumber() const {return i;}
};

class q_zone
{
	std::vector<std::string>  questions;
	size_t z_property;
private:
	size_t LoadZoneText(std::istream &is, int pro);
	
	void push_back(std::string q);
public:
	size_t LoadZoneBin( std::istream & is);
	//size_t q_number() const {return 1;}
	size_t difficult() const;
	// for binary input
	q_zone();
	// for text input
	q_zone(std::istream &is, int pro);
	
	size_t size() const;
	std::string operator[](int n) const;
	void SaveToBinFile( std::ostream &is) const;
	//friend std::ostream& operator <<(std::ostream& os, const q_zone & z);
};

class Database {
	std::vector<q_zone> zones;
public:
	Settings set;
	size_t LoadFromBinFile( std::istream &is);
	size_t LoadFromTextFile( std::istream &is);
	void SaveToBinFile( std::ostream &os) const ;
	size_t size() const;// {return zones.size();}
	q_zone & operator[](int n)  { return zones[n];}
	q_zone  operator[]  (int n) const { return zones[n];}
};

