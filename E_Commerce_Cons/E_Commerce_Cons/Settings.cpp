#include "Settings.h"
#include "Items.h"
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<map>
#include <fstream>
#include <sstream>

using namespace std;

products::products()
{
	quantity = 0;
}


products::~products()
{
}

//buy function
void products::buy(string email, map<string, products>&sells, map<string, user>&mp) {
	//load the file of products
	sells.clear();
	ifstream SRfile("store.txt", ios::app);
	if (SRfile.is_open()) {
		string name, mail;
		int quant;
		double price;
		while (SRfile >> name >> mail >> quant >> price)
		{
			sells[name].quantity += quant;
			sells[name].store_of_user[mail].Amount += quant;
			sells[name].store_of_user[mail].Price = price;
		}
	}
	SRfile.close();

	//showing all product in our store
	cout << "                       Welcome To Our Store Which Contain              " << endl << endl;
	map <string, products>::iterator sit;
	map< string, Items>::iterator it;
	for (sit = sells.begin(); sit != sells.end(); ++sit) {
		if (sit->second.quantity)
			cout << "The product name :" << sit->first << endl << "The quantity of this product :" << sit->second.quantity << endl << endl;
	}
	while (1) {
		string name;
		cout << "Enter The Name Of The Product That Want To Buy : ";
		cin >> name;
		if (sells[name].quantity == 0) {
			cout << "There Is No Product Available By This Name" << endl;
			return;
		}
		else {
			int indx = 1;
			vector<string> v;
			map<string, Items>::iterator it;
			for (it = sells[name].store_of_user.begin(); it != sells[name].store_of_user.end(); ++it, ++indx) {
				cout << "Product Number : " << indx << endl;
				cout << "The Owner Of The Product : " << mp[it->first].username << endl;
				cout << "The  Quantity : " << it->second.Amount << endl;
				cout << "The Price :" << it->second.Price << " $" << endl << endl;
				v.push_back(it->first);
			}
			int number;
			cout << "Enter The Product Number That You Want To Buy : ";
			cin >> number;
			if (number <= 0 || number > indx) {
				cout << "WRONG INPUT" << endl;
			}
			else {
				mp[email].cart[name] = v[number - 1];
				cout << "The product has added to your cart" << endl;
			}
			cout << "to buy anothe product press 1 else press any key : ";
			int operation;
			cin >> operation;
			if (operation == 1)
				continue;
			else
				break;
		}
	}
	ofstream UCfile("cart.txt", ios::app);
	if (UCfile.is_open()) {
		map < string, user >::iterator it;
		map<string, string>::iterator sit;
		for (it = mp.begin(); it != mp.end(); ++it) {
			for (sit = it->second.cart.begin(); sit != it->second.cart.end(); ++sit) {
				// cart name product - email of owner -
				UCfile << email << " " << sit->first << " " << sit->second << endl;
			}
		}
	}
	UCfile.close();
}



void products::Cart(string mail, map < string, user >&mp, map <string, products>&sells) {
	cout << "                               Your Cart Contain :" << endl;
	map<string, string>::iterator it;
	for (it = mp[mail].cart.begin(); it != mp[mail].cart.end(); ++it) {
		// it->second email the owner
		cout << "The product name : " << it->first << "    " << "The product owner : " << mp[it->second].username
			<< endl << "The price : " << sells[it->first].store_of_user[it->second].Price << " $           "
			<< "The quantity : " << sells[it->first].store_of_user[it->second].Amount << endl << endl;
	}
	map< string, int > v;
	int price = 0;
	while (1) {
		cout << "To remove from the cart press(1) , to confirm press(2) , to end press(0) : ";
		int x; cin >> x;
		if (x == 1) {
			cout << "Enter the product name that you wanna remove : ";
			string name;
			cin >> name;
			if (mp[mail].cart[name] == "")
				cout << "Invalid \n";
			else mp[mail].cart.erase
			(name);
			if (v[name] > 0)
				v.erase(name);

			continue;
		}
		else if (x == 2) {
			cout << "Enter the product name : ";
			string name;
			cin >> name;
			cout << "The quantity that you want to buy : ";
			int qnt;
			cin >> qnt;
			if (sells[name].store_of_user[mp[mail].cart[name]].Amount<qnt)
				cout << "Invalild\n";
			else
				v[name] += qnt;
		}
		else if (x == 0) {
			if (v.size() > 0) {
				map< string, int >::iterator it;
				for (it = v.begin(); it != v.end(); ++it) price += it->second*sells[it->first].store_of_user[mp[mail].cart[it->first]].Price;
				if (price > mp[mail].cach) {
					cout << "Your money isn't enough \n";
				}
				else {
					cout << "The price is " << price << " $ to confirm press(1) else press any\n";
					int operation;
					cin >> operation;
					if (operation == 1) {
						mp[mail].cach -= price;
						map<string, int>::iterator it;
						for (it = v.begin(); it != v.end(); ++it) {
							mp[mp[mail].cart[it->first]].cach += it->second * sells[it->first].store_of_user[mp[mail].cart[it->first]].Price;
							sells[it->first].store_of_user[mp[mail].cart[it->first]].Amount -= it->second;
							mp[mail].cart.erase(it->first);
						}
					}
				}
			}
			break;
		}
		else
			cout << "Invalid";
	}
	remove("data.txt");
	ofstream Ufile("data.txt", ios::app);
	if (Ufile.is_open()) {
		map < string, user >::iterator it;
		for (it = mp.begin(); it != mp.end(); ++it)
			Ufile << it->first << " " << it->second.username << " " << it->second.password << " " << it->second.cach << endl;
	}
	Ufile.close();

	remove("store.txt");
	ofstream USfile("store.txt", ios::app);
	if (USfile.is_open()) {
		map <string, products>::iterator sit;
		map< string, Items>::iterator it;
		for (sit = sells.begin(); sit != sells.end(); ++sit) {
			for (it = sit->second.store_of_user.begin(); it != sit->second.store_of_user.end(); ++it) {
				USfile << sit->first << " " << it->first << " " << it->second.Amount << " " << it->second.Price << "\n";
			}
		}
	}
	USfile.close();

	remove("cart.txt");
	ofstream UCfile("cart.txt", ios::app);
	if (UCfile.is_open()) {
		for (map<string, user>::iterator it = mp.begin(); it != mp.end(); ++it) {
			for (map<string, string>::iterator sit = it->second.cart.begin(); sit != it->second.cart.end(); ++sit) {
				UCfile << it->first << " " << sit->first << " " << sit->second << endl;
			}
		}
	}
	UCfile.close();
}
