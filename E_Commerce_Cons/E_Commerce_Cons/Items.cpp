#include "Items.h"
#include <iostream>
#include<string>
using namespace std;

Items::Items()
{
	Name = "";
	Category = "";
	Price = 0;
	Sale = 0;
	Description = "";
	Colour = "";
	Amount = 0;
}

Items::Items(string name, string category, double price, int amount, double sale, string description, string colour,string brand)

{
	Name = name;
	Category = category;
	Price = price;
	Sale = sale;
	Description = description;
	Colour = colour;
	Brand = brand;
	Amount = amount;
}


Items::~Items()
{
}
