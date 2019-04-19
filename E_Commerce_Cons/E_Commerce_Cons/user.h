#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

class user
{
public:
   //key :name of product - value: email of product owner
	map<string, string> cart ;
	string email, username, password;
	double cach;
	bool valid;
	user();
	~user();
	void regist( map < string , user > &p );
	string login( map < string , user > p);
};

