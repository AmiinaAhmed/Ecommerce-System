#include "HashTable.h"
#include<iostream>
#include <algorithm>
#include<vector>
#include <sstream>
#include <fstream>
#include<limits>
using namespace std;

HashTable::HashTable()
{
	Brand_Name = "";
//	Product = { "", (0) };
}
HashTable::HashTable(string br, unordered_map<string, vector<Items>> pr)
{
	Brand_Name = br;
	Product = pr;

}

void HashTable::Add_Item(bool readFlag, vector<Items> &v, string name, string category, double price, int amount, double sale, string description, string color, string brand)
{
	Items insert(name, category, price, amount, sale, description, color, brand);
	Product[Brand_Name] = vector<Items>();
	Product[brand].push_back(insert);
	
	
	v.push_back(insert);

	if (!readFlag) {

		remove("data.txt");

		ofstream SWfile("data.txt", ios::app);
		if (SWfile.is_open())
		{
			for (int i = 0; i < v.size(); i++) {
				cout << i << endl;
				SWfile << v[i].Name << " " << v[i].Category << " " << v[i].Price << " " << v[i].Amount << " " << v[i].Sale << " " << v[i].Description << " " << v[i].Colour << " " << v[i].Brand << "\n";
			}
		}
		SWfile.close();
	}
}

void HashTable::List_By_Brands(string brand)
{

	HashIterator = Product.find(brand);
	if (HashIterator != Product.end())
	{
		cout << " the items for this brand is  " << endl;
		for (vector<Items>::size_type i = 0; i < HashIterator->second.size(); i++)
		{
			cout << " ______________________________________________________" << endl;
			cout << "ID : " << i + 1 << endl;
			cout <<"Category : "<<(HashIterator->second)[i].Category << endl;
			cout <<"name : " << (HashIterator->second)[i].Name << endl;
			cout <<"price : " << (HashIterator->second)[i].Price << endl;
			cout <<"discount : " << (HashIterator->second)[i].Sale << endl;
			cout <<"Colour : "<< (HashIterator->second)[i].Colour << endl;
			cout <<"description : " << (HashIterator->second)[i].Description << endl;
			cout <<"Brand  : " << (HashIterator->second)[i].Brand << endl;


		}
		   cout << endl << "___________________________________________" << endl;
	}
	else
		cout << "not found " << endl;


}

void HashTable::List_All()
{
  
	for (HashIterator = Product.begin(); HashIterator != Product.end();HashIterator++)
	{
	//	cout << " the items for this brand is : " << endl;
		for (vector<Items>::size_type i = 0; i < HashIterator->second.size(); i++)
		{
			cout << " ______________________________________________________" << endl;
			cout << "Category : " << (HashIterator->second)[i].Category << endl;
			cout << "name : " << (HashIterator->second)[i].Name << endl;
			cout << "price : " << (HashIterator->second)[i].Price << endl;
			cout << "discount : " << (HashIterator->second)[i].Sale << endl;
			cout << "Colour : " << (HashIterator->second)[i].Colour << endl;
			cout << "description : " << (HashIterator->second)[i].Description << endl;
			cout << "Brand  : " << (HashIterator->second)[i].Brand<< endl;

		}

		cout << endl << "___________________________________________" << endl;
	}


}

void HashTable::list_by_category(string category)
{
	
	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		
		for (vector<Items>::size_type i = 0; i < HashIterator->second.size(); i++)
		{
			if ((HashIterator->second)[i].Category == category)
			{

				cout << " ______________________________________________________" << endl;
				cout << "Category : " << (HashIterator->second)[i].Category << endl;
				cout << "name : " << (HashIterator->second)[i].Name << endl;
				cout << "price : " << (HashIterator->second)[i].Price << endl;
				cout << "discount : " << (HashIterator->second)[i].Sale << endl;
				cout << "Colour : " << (HashIterator->second)[i].Colour << endl;
				cout << "description : " << (HashIterator->second)[i].Description << endl;
				cout << "Brand  : " << (HashIterator->second)[i].Brand << endl;
			}
			else
				cout << "not found " << endl;
		}
		cout << endl << "___________________________________________" << endl;
	}



}

void HashTable::List_By_color(string color)
{
	

	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{

		for (vector<Items>::size_type i = 0; i < HashIterator->second.size(); i++)
		{
			if ((HashIterator->second)[i].Colour == color)
			{

				cout << " ______________________________________________________" << endl;
				cout << "Category : " << (HashIterator->second)[i].Category << endl;
				cout << "name : " << (HashIterator->second)[i].Name << endl;
				cout << "price : " << (HashIterator->second)[i].Price << endl;
				cout << "discount : " << (HashIterator->second)[i].Sale << endl;
				cout << "Colour : " << (HashIterator->second)[i].Colour << endl;
				cout << "description : " << (HashIterator->second)[i].Description << endl;
				cout << "Brand  : " << (HashIterator->second)[i].Brand << endl;

			}
			else
				cout << "not found " << endl;
		}

		
		cout << endl << "___________________________________________" << endl;
	}



}
void HashTable::Edit_Item()
{
	string EditBrand;
	cout << "Here is all the brands we have " << endl;
	cout << endl<< "___________________________________________" << endl;


	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}

	cout << "Choose the brand you want to edit in : ";
	cin >> EditBrand;
	List_By_Brands(EditBrand);
	int EditID;
	cout << "choose Item ID to Edit it's Data : ";
	cin >> EditID;
	while(cin.fail())
	{
		cout << "Error input\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "choose Item ID to Edit it's Data : ";
		cin >> EditID;
	}
	cout << "Enter_1_to edit Name Of item \nEnter_2_to edit category of item  \nEnter_3_to edit price \nEnter_4_to edit sale price \nEnter_5_to edit description \nEnter_6_to edit color of item \nEnter_7_to edit brand of item \n ";
	int choice;
	cin >> choice;
	while (cin.fail())
	{
		cout << "Error input\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cin >> choice;
	}
	string change;
	cout << "enter your new value\n";
	cin >> change;
	switch (choice)
	{
	case 1:
		(HashIterator->second)[EditID - 1].Name = change;
		cout << "UPDATED\n";

		break;

	case 2:
		(HashIterator->second)[EditID - 1].Category = change;
		cout << "UPDATED\n";

		break;

	case 3:
		(HashIterator->second)[EditID - 1].Price =stod( change);
		cout << "UPDATED\n";

		break;

	case 4:
		(HashIterator->second)[EditID - 1].Sale =stod( change);
		cout << "UPDATED\n";

		break;

	case 5:
		(HashIterator->second)[EditID - 1].Description = change;
		cout << "UPDATED\n";

		break;

	case 6:
		(HashIterator->second)[EditID - 1].Colour = change;
		cout << "UPDATED\n";

		break;

	case 7:
		(HashIterator->second)[EditID - 1].Brand = change;
		cout << "UPDATED\n";

		break;

	default:
		cout << "Wrong input" << endl;
		cout << "UPDATED\n";

		break;
	}


}
void HashTable::Delete_Item(vector<Items> &v)
{
	string EditBrand;
	cout << "Here is all the brands we have " << endl;
	cout << endl << "___________________________________________" << endl;
	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}
	cout << "Choose the brand you want to Delete in : ";
	cin >> EditBrand;
	
	List_By_Brands(EditBrand);
	int EditID;

	cout << "choose Item ID to Delete it : ";
	cin >> EditID;
	while (cin.fail())
	{
		cout << "Error input\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "choose Item ID to Delete it : ";
		cin >> EditID;
	}
	int pos = EditID - 1;
	swap(HashIterator->second[pos], HashIterator->second.back());
	swap(v[pos], v[v.size() - 1]);
	HashIterator->second.pop_back();
	v.pop_back();
	cout << "Deleted :(\n";
}
void HashTable::Add_Brand(string brand)
{
	Product[brand];
	cout << "Brand " + brand + " added "<<endl;

}

void HashTable::Edit_Brand()
{
	string NewBrandName,OldBrandName;
	cout << "Here is all the brands we have " << endl;
	cout << "___________________________________________" << endl;
	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}
	cout << "Choose the brand you want to edit it : "; cin >> OldBrandName;
	cout << "Enter the New Brand Name ... " << endl; cin >> NewBrandName;
	HashIterator = Product.find(OldBrandName);
	for (vector<Items>::size_type i = 0; i < HashIterator->second.size(); i++)
	{
		(HashIterator->second)[i].Brand = NewBrandName;
	}
	vector<Items> temp = HashIterator->second;
	Product.erase(OldBrandName);
	Product[NewBrandName]=temp;
	
	cout << "Here is all the brands we have " << endl;
	cout << endl << "___________________________________________" << endl;


	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}
}

void HashTable::Delete_Brand()
{
	string DeletedBrand;
	cout << "Here is all the brands we have " << endl;
	cout << "___________________________________________" << endl;
	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}
	cout << "Choose the brand you want to DELETE it : ";
	cin >> DeletedBrand;	
	Product.erase(DeletedBrand);
	cout << "Here is all the brands we have " << endl;
	cout << "___________________________________________" << endl;
	for (HashIterator = Product.begin(); HashIterator != Product.end(); HashIterator++)
	{
		cout << HashIterator->first << endl;
	}
}
HashTable::~HashTable()
{

}
