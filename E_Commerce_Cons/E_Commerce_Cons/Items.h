#pragma once
#include <iostream>
#include<string>
using namespace std;
 class Items
{
public:
	string Name;
	string Category;
	double Price;
	double Sale;
	string Description;
	string Colour;
	string Brand;
	int Amount;

	Items();
	Items(string, string, double, int, double, string, string,string);
	~Items();
};

