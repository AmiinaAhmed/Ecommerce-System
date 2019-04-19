#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <queue>
#include <algorithm>
#include "Items.h"
using namespace std;
class Sorting
{
public:
	//the member :
	vector < Items > Product;
	//class functions:
	Sorting();
	Sorting(vector<Items>);
	void sorting_by(vector<Items> v, int cho);
	/*void remove(vector<Items>& vec);*/
	~Sorting();
};

