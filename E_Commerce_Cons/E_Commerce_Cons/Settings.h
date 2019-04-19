#pragma once
#include "user.h"
#include "Items.h"
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<map>
#include <fstream>
#include <sstream>
using namespace std;
class products {
public:
	//how many do you want to buy 
	int quantity;
	//key: email of product's owner , value: class contain data of each of product of a specific user
	map<string, Items> store_of_user;
	products();
	~products();
	void buy(string email, map<string, products>&sells, map<string, user>&mp);
	void Cart(string mail, map < string, user >&mp, map <string, products>&sells);
};
