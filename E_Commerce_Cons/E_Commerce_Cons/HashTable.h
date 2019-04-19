#pragma once
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include"Items.h"
#include<list>
using namespace std;
class HashTable
{
public:
	string Brand_Name;
	unordered_map <string, vector<Items>> Product;
	unordered_map <string, vector<Items>>::iterator HashIterator;
	Items InsertItem;

	HashTable();
	HashTable(string, unordered_map<string, vector<Items>>);
	void List_By_Brands(string Brand);
	void List_All();
	void list_by_category(string category);
	void List_By_color(string color);
	void Add_Item(bool, vector<Items> &, string, string, double, int, double,string, string, string);
	void Edit_Item();
	void Delete_Item(vector<Items> &);
	void Add_Brand(string brand);
	void Edit_Brand();
	void Delete_Brand();
	~HashTable();
};

