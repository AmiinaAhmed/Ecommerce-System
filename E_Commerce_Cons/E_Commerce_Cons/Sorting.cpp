#include "Sorting.h"
#include <iostream>
#include<string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;



Sorting::Sorting()
{
	Product = {};
}

Sorting::Sorting(vector<Items> Vec)
{
	Product = Vec;
}

Sorting::~Sorting()
{
}

bool Price_Asc(Items & I1, Items & I2)
{
	return (I1.Price < I2.Price);
}
bool Price_Dec(Items & I1, Items & I2)
{
	return (I1.Price > I2.Price);
}
bool Amount_Asc(Items & I1, Items & I2)
{
	return (I1.Amount < I2.Amount);
}
bool Amount_Dec(Items & I1, Items & I2)
{
	return (I1.Amount > I2.Amount);
}
bool Name_Asc(Items & I1, Items & I2)
{
	return (I1.Name < I2.Name);
}
bool Name_Dec(Items & I1, Items & I2)
{
	return (I1.Name > I2.Name);
}

void Sorting::sorting_by(vector<Items> v, int cho)
{

	vector<Items>::iterator it;

	if (cho == 1)//by price Asc
	{
		sort(v.begin(), v.end(), Price_Asc);
		vector<Items>::iterator it;
		cout << "the product sorted by PRICE IN ASCENDING Order is :\n ";
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}

	}
	else if (cho ==2)//by Price Dec
	{
		sort(v.begin(), v.end(), Price_Dec);
		vector<Items>::iterator it;
		cout << "the product sorted by PRICE IN DESCENDING Order is :\n ";

		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}
	}
	else if (cho == 3) //by Amount Asc 
	{
		sort(v.begin(), v.end(), Amount_Asc);
		vector<Items>::iterator it;
		cout << "the product sorted by AMOUNT  IN ASCENDING Order is :\n ";
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}
	}
	else if (cho == 4)//by Amount Dec
	{
		sort(v.begin(), v.end(), Amount_Dec);
		vector<Items>::iterator it;
		cout << "the product sorted by AMOUNT IN DESCENDING Order is :\n ";
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}
	}
	else if (cho ==5) 
	{
		sort(v.begin(), v.end(), Name_Asc);
		vector<Items>::iterator it;
		cout << "the product sorted by NAME from A to Z is :\n ";
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}
	}
	else if (cho == 6)
	{
		sort(v.begin(), v.end(), Name_Dec);
		vector<Items>::iterator it;
		cout << "the product sorted by NAME from Z to A is :\n ";
		for (it = v.begin(); it != v.end(); it++)
		{
			cout << "Name :  " << (*it).Name
				<< "\nAmount : " << (*it).Amount
				<< "\nCategory : " << (*it).Category
				<< "\nPrice : " << (*it).Price
				<< "\nSale : " << (*it).Sale
				<< "\nDescription : " << (*it).Description
				<< "\nColor : " << (*it).Colour
				<< "\nColor : " << (*it).Brand <<
				"\n______________________________________________________________________ " << endl;
		}
	}
	else cout << "Sorry Enter Correct Choice \n";
}

//void Sorting::remove(vector<Items>& vec) {
//	int pos;
//	vector<Items>::iterator it;
//	cout << "\nwhich item do you want to remove : \n";
//	for (it = vec.begin(); it != vec.end(); it++)
//	{
//		cout << "its no: " << distance(vec.begin(), it) << " the Name:  " << (*it).Name << endl;
//	}
//	cin >> pos;
//	swap(vec[pos], vec.back());
//	vec.pop_back();
//}
