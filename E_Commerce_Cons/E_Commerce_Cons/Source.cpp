#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<map>
#include <fstream>
#include <sstream>
#include <limits>
#include "user.h"
#include "HashTable.h"
#include "Items.h"
#include "Sorting.h"
using namespace std;

struct order {
	int quantity;
	double price;
	string name;
};

// u : object of user class
user u;
// p : object of products class
//products p;
//hashTable key : brand and value : class of item
HashTable ListProduct;
vector<Items> productsVec;
map<string, Items> searchProd;
map<string, bool> isProdAvailable;
//key : email of user , value: class contain data of each user
map < string, user > mp;

string CurUsrMail;

map<string, vector<order> > orders;



void clearInputBuffer() {
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}



void buy(string name, int quantitiy, double price) {
	orders[CurUsrMail].push_back({ quantitiy, price, name });
	remove("orders.txt");

	ofstream SRfile("orders.txt", ios::app);
	if (SRfile.is_open())
	{
		for (map<string, vector<order>>::iterator it = orders.begin(); it != orders.end(); it++) {
			vector<order> temp = it->second;
			for (int i = 0; i < temp.size(); i++) {
				SRfile << it->first << " " << temp[i].name << " " << temp[i].quantity << " " << temp[i].price << endl;
			}
		}
	}
	else {
		cout << "there is Endl to load the file of products" << endl;
	}
	SRfile.close();
}


void readOrders() {
	ifstream SRfile("orders.txt", ios::app);
	if (SRfile.is_open())
	{
		string mail, name;
		int quantitiy;
		double price;
		while (SRfile >> mail >> name >> quantitiy >> price)
		{
			orders[mail].push_back({ quantitiy, price, name });
		}
	}
	else {
		cout << "there is Endl to load the file of products" << endl;
	}
	SRfile.close();
}


void ReadDataForUser() 
{
	ifstream Rfile("dataT.txt", ios::app);
	if (Rfile.is_open()) {
		string MAIL, NAME, PASS;
		double MONEY;
		while (Rfile >> MAIL >> NAME >> PASS >> MONEY) {
			mp[MAIL].username = NAME;
			mp[MAIL].password = PASS;
			mp[MAIL].cach = MONEY;
			mp[MAIL].valid = 1;
		}
	}
	else {
		cout << "there is Endl to load the file of users" << endl;
	}
	Rfile.close();
}

void ReadStore() 
{
	//load the data of products in our data structure
	ifstream SRfile("data.txt", ios::app);
	if (SRfile.is_open()) 
	{
		string Name, Category, Description, Colour, Brand;
		double Price, Sale;
		int Amount;
		while (SRfile >> Name >> Category >> Price >> Amount >> Sale >> Description >> Colour >> Brand)
		{
			ListProduct.Add_Item(true , productsVec, Name, Category, Price, Amount, Sale, Description, Colour, Brand);
			Items I(Name, Category, Price, Amount, Sale, Description, Colour, Brand);
			//productsVec.push_back(I);
			isProdAvailable[Name] = true;
			searchProd[Name] = I;
		}
	}
	else {
		cout << "there is Endl to load the file of products" << endl;
	}
	SRfile.close();
}

void ReadDataForShoppingCart() {
	//load the data of cart in our data structure
	ifstream UCRfile("cart.txt", ios::app);
	if (UCRfile.is_open()) {
		string name, mail, a;
		while (UCRfile >> a >> name >> mail) {
			mp[a].cart[name] = mail;
		}
	}
	else {
		cout << "there is Endl to load the file of carts" << endl;
	}
	UCRfile.close();
}

//min_occuer to cal. the occurrences of products
#define min_sup 2
//for each costoumer/transaction has unique ID & number of products
struct transaction {
	string transactionID;
	vector<string> products;
};
//for each product Set has product List and count for each one (number_of_occurrences)
struct productSet {
	vector<string> productList;
	int count;
};
//how many set of product list in the each table 
int depth = 1;
//vector has all the product set that with the min_sup(min_occurrences)
vector<productSet> allProductSetWithMinSup;

//take an every input and convert the input to an string if it not and push the product for every transaction
transaction stringToTransaction(string input) {
	/*convert every input to string*/
	istringstream iss(input);
	transaction newTransaction;
	iss >> newTransaction.transactionID;
	/*push all the product for each transaction*/
	string product;
	while (iss >> product)
		newTransaction.products.push_back(product);
	return newTransaction;
}
//take vector of type (transaction) and push every input from file to it 
//reads the transactions from the file
void inputTransactions(vector<transaction> &transactions) {
	string input;
	while (getline(cin, input)) transactions.push_back(stringToTransaction(input));
}
//to find in each transactions the unique product
void findUniqueProduct(vector<string> &uniqueProduct, vector<transaction> transactions) {
	map<string, bool> productFound;
	for (int i = 0; i < transactions.size(); i++) {
		for (int j = 0; j < transactions[i].products.size(); j++) {
			if (!productFound[transactions[i].products[j]]) {
				uniqueProduct.push_back(transactions[i].products[j]);
				productFound[transactions[i].products[j]] = true;
			}
		}
	}
}
//to make an set of product list from the unique products
void makeSetOfProductList(vector<productSet> &setofProductList, vector<string> uniqueProduct) {
	for (int i = 0; i < uniqueProduct.size(); i++) {
		productSet newSetofProductList;
		newSetofProductList.productList.push_back(uniqueProduct[i]);
		setofProductList.push_back(newSetofProductList);
	}
}
//return if it occuer more than or equal the min_occurrences (min_sup)
bool isOccuerIn(transaction currentTransaction, productSet currentProductList) {
	int count = 0;
	for (int i = 0; i < currentProductList.productList.size(); i++) {
		for (int j = 0; j < currentTransaction.products.size(); j++) {
			if (currentProductList.productList[i] == currentTransaction.products[j]) {
				count++; break;
			}
		}
	}
	if (count >= currentProductList.productList.size()) return true;
	return false;
}
//cal. how many times the productList has occuer for the each iteration 
int testOccurance(productSet currentProductList, vector<transaction> transactions) {
	int count = 0;
	for (int i = 0; i < transactions.size(); i++)
		if (isOccuerIn(transactions[i], currentProductList))
			count++;
	return count;
}
//to find the selected Set Of Product List for each set of product list 
void selectProductList(vector<productSet> &setOfProductList, vector<transaction> transactions, vector<productSet> &selectedSetOfProductList) {
	for (int i = 0; i < setOfProductList.size(); i++) {
		int occurance = testOccurance(setOfProductList[i], transactions);
		setOfProductList[i].count = occurance;
		if (setOfProductList[i].count >= min_sup) {
			allProductSetWithMinSup.push_back(setOfProductList[i]);
			selectedSetOfProductList.push_back(setOfProductList[i]);
		}
	}
}
//to print the table for each iteration with how many occurrences 
void printTable(string tableType, vector<productSet> setOfProductList) {
	cout << "Table " << tableType << depth << endl;
	for (int i = 0; i < setOfProductList.size(); i++) {
		for (int j = 0; j < setOfProductList[i].productList.size(); j++) {
			cout << setOfProductList[i].productList[j] << " ";
		}
		cout << "  --  " << setOfProductList[i].count << endl;
	}

}
//combines pairs of productSet
productSet getNewCombination(productSet set1, productSet set2) {
	productSet newSet;
	map<string, bool> taken;
	for (int i = 0; i < set1.productList.size(); i++) {
		if (!taken[set1.productList[i]]) {
			newSet.productList.push_back(set1.productList[i]);
			taken[set1.productList[i]] = true;
		}
	}
	for (int i = 0; i < set2.productList.size(); i++) {
		if (!taken[set2.productList[i]]) {
			newSet.productList.push_back(set2.productList[i]);
			taken[set2.productList[i]] = true;
		}
	}
	return newSet;
}
//return if the suffix of Combination exist or not 
bool suffixExist(vector<productSet> selectedSetOfProductList, productSet tempCombination) {
	for (int i = 0; i < selectedSetOfProductList.size(); i++) {
		int count = 0;
		for (int j = 0; j < selectedSetOfProductList[i].productList.size(); j++) {
			for (int k = 1; k < tempCombination.productList.size(); k++) {
				if (tempCombination.productList[k] == selectedSetOfProductList[i].productList[j])
					count++;
			}
		}
		if (count == selectedSetOfProductList[i].productList.size()) {
			cout << count << endl;
			return true;
		}
	}
	return false;
}
//calculates the frequency of a pair of set Of Product List
void operate(vector<productSet> setOfProductList, vector<transaction> transactions) {
	vector<productSet> selectedSetOfProductList;
	selectProductList(setOfProductList, transactions, selectedSetOfProductList);
	if (selectedSetOfProductList.size() < 1) return; //if there is no selectedSetOfProductList so will stop genrate more tables
	printTable("L", selectedSetOfProductList);
	cout << endl;
	vector<productSet> newSetofProductList;
	if (selectedSetOfProductList[0].productList.size() == 1) {
		for (int i = 0; i < selectedSetOfProductList.size() - 1; i++) {
			for (int j = i + 1; j < selectedSetOfProductList.size(); j++) {
				productSet newSet;
				newSet.productList.push_back(selectedSetOfProductList[i].productList[0]);
				newSet.productList.push_back(selectedSetOfProductList[j].productList[0]);
				newSetofProductList.push_back(newSet);
			}
		}
	}
	else
		for (int i = 0; i < selectedSetOfProductList.size() - 1; i++)
			for (int j = i + 1; j < selectedSetOfProductList.size(); j++)
				if (selectedSetOfProductList[i].productList[0] == selectedSetOfProductList[j].productList[0]) {
					productSet tempCombination = getNewCombination(selectedSetOfProductList[i], selectedSetOfProductList[j]);
					if (suffixExist(selectedSetOfProductList, tempCombination))
						newSetofProductList.push_back(tempCombination);
				}
	depth++; // increase set of product list in the each table 
	operate(newSetofProductList, transactions);
}
void CustomerMenu()
{
	cout << "------------------------------------------------------------" << endl;
	cout << "Customer Menu" << endl
		<< "1. Search for a product" << endl
		<< "2. List Products" << endl
		<< "3. Sorting The Products" << endl
		<< "4. Place an order" << endl 
		<< "5. View purchases" << endl
		<< "6. View Most Items Repeated" << endl//not yet
		<< "7. Quit" << endl;
	int command; 
	cin >> command;
	//clearInputBuffer();
	if (command == 1)// Search
	{
		string itemName = "";
		cout << "Please input item name" << endl;
		//clearInputBuffer();
		cin >> itemName;
		cout << "--->" << itemName << endl;

		if(isProdAvailable[itemName])
		{
			Items I = searchProd[itemName];
			cout << " ______________________________________________________" << endl;
			cout << "Category : " << I.Category << endl;
			cout << "name : " << I.Name << endl;
			cout << "price : " << I.Price << endl;
			cout << "discount : " << I.Sale << endl;
			cout << "Color : " << I.Colour << endl;
			cout << "description : " << I.Description << endl;
			cout << "Brand  : " << I.Brand << endl;

		}
		else cout << "Can't find item with this name " << itemName << endl;

	}
	else if(command == 2)//list 
	{
		string  view;
		string viewCat;
		int choice = 0;

		do
		{
			cout << " Enter_1_to list by brand :\n Enter_2_to list all products : \n Enter_3_to list by category \n Enter_4_to list by color \n Enter_5_ to exit \n ";
			cin >> choice;
			if (choice == 1)//list by brand
			{
				cout << "Enter brand to view " << endl;
				cin >> view;
				ListProduct.List_By_Brands(view);
			}
			else if (choice == 2)//list all product
			{
				ListProduct.List_All();
			}
			else if (choice == 3)//list by category
			{
				cout << "Enter category : ";
				cin >> viewCat;
				ListProduct.list_by_category(viewCat);
			}
			else if (choice == 4)//list by color
			{
				string ViewColor;
				cout << "Enter color to view items with this color " << endl;
				cin >> ViewColor;
				ListProduct.List_By_color(ViewColor);
			}

			else if (choice != 5)//error in input 
			{
				cout << "Invalid Input!\n";
			}
		} while (choice != 5);
	}

	else if(command == 3)//sorting
	{


			Sorting test (productsVec);
			int choice;
			cout << "Show the prodct sorted by : \n1-Price_Ascending \n2-Price_Descending \n3-Amount_Ascending \n4-Amount_Descending \n5-Name A-Z \n6-Name Z-A : \n";
			cin >> choice;
			test.sorting_by(productsVec, choice);

	}

	else if(command == 4)
	{
		ListProduct.List_All();
		cout << "Enter product's name: ";
		string prodName; cin >> prodName;
		if (!isProdAvailable[prodName]) {
			cout << "This product is unavailable" << endl;
		}
		else {
			cout << "Enter Quantitiy:";
			int q;
			cin >> q;
			for (int i = 0; i < productsVec.size(); i++) {
				if (productsVec[i].Name == prodName) {
					if (productsVec[i].Amount < q) {

						cout << "The available quantitiy is " << productsVec[i].Amount << endl;
						

					}			
					else {
						buy(prodName, q, productsVec[i].Price*q);
						cout << "You ordered " << q << " of " << prodName << endl;
					}

					return;
				}
			}
			
		}
	}
	else if (command == 5) {
		readOrders();
		cout << "Your Orders History:" << endl;
		vector<order> v = orders[CurUsrMail];
		for (int i = 0; i < v.size(); i++) {
			cout << "Name:" << v[i].name << endl << "Quantity:" << v[i].quantity << endl << "Unit Price:" << v[i].price / v[i].quantity << endl << "Total:" << v[i].price << endl;
		}
		cout << "---------------------------------------" << endl;
	}
	else if (command == 6) {
		/*FILE * stream;
	    freopen(&stream ,"orders.txt", "r", stdin);

		vector<transaction> transactions;
		vector<string> uniqueProduct;
		vector<productSet> setofProductList;

		inputTransactions(transactions);
		findUniqueProduct(uniqueProduct, transactions);
		makeSetOfProductList(setofProductList, uniqueProduct);
		operate(setofProductList, transactions);*/
	}
	else{
		cout << "Invalid Input\n";
	}
}


void resetFile() 
{
	remove("data.txt");

	ofstream SWfile("data.txt", ios::app);
	if (SWfile.is_open())
	{
		for (int i = 0; i < productsVec.size(); i++) {
			cout << i << endl;
			SWfile << productsVec[i].Name << " " << productsVec[i].Category << " " << productsVec[i].Price << " " << productsVec[i].Amount << " " << productsVec[i].Sale << " " << productsVec[i].Description << " " << productsVec[i].Colour << " " << productsVec[i].Brand << "\n";
		}
	}
	SWfile.close();
}


void AdminMenu()
{
	cout << "Administrator Menu" << endl
		<< "1. Add Brand" << endl//done
		<< "2. Update Brand" << endl//done
		<< "3. Delete Brand" << endl//done
		<< "4. Add Item For Specific Brand" << endl //done
		<< "5. Update Item In Specific Brand" << endl //done
		<< "6. Delete Item In Specific Brand" << endl//done
		<< "7. Quit" << endl;
	int command; 
	cin >> command;
	//clearInputBuffer();
    if (command == 1)//add brand fn
	{ 
		string NewBrand;
		cout << "The Name : \n";
		cin >> NewBrand;
		ListProduct.Add_Brand(NewBrand);
	}
	else if(command==2)// update brand fn
	{
		ListProduct.Edit_Brand();
	}
	else if (command == 3)//Delete brand fn
	{
		ListProduct.Delete_Brand();
	}
	else if (command == 4)//Add Item For Specific Brand
	{
		string name;
		string category;
		double price;
		int amount; 
		double sale;
		string description;
		string color; 
		string brand;
		cout << "Enter the Product Detelis : \n";
		cout << "Brand : ";
		cin >> brand;
		cout << "\nProduct Name : ";
		cin >> name;
		cout << "\nCategory : ";
		cin >> category;
		cout << "\nPrice : ";
		cin >> price;
		cout << "\nAmount : ";
		cin >> amount;
		cout << "\nSale : ";
		cin >> sale;
		cout << "\nDescription : ";
		cin >> description;
		cout << "\nProduct Color : ";
		cin >> color;
		ListProduct.Add_Item(false, productsVec, name,category,price,amount,sale,description,color,brand);
	}
	else if (command == 5)//Update Item In Specific Brand
	{
		ListProduct.Edit_Item();
	}
	else if (command == 6)//Delete Item In Specific Brand
	{
		ListProduct.Delete_Item(productsVec);
		resetFile();
	}

}

void Greeting()
{
	cout << "                                      (: Welcome To ONLINE SHOPPING :)             " << endl << endl;
	string operation;
	while (true) {
		cout << "                                          To Registration Press (1)\n                                             To Login Press (2)\n";
		cin >> operation;
		cout << endl << endl;
		if (operation != "1" && operation != "2") {
			cout << "ERROR Invalid Input" << endl;
			continue;
		}
		if (operation == "1") {
			u.regist(mp);
			continue;
		}
		if (operation == "2") {
			CurUsrMail = u.login(mp);
			if (CurUsrMail != "no") {
				while (true) {
					cout << "Please Choose Menu Type:" << endl
						<< "1. Customer Menu" << endl
						<< "2. Admin Menu" << endl
						<< "3. Exit" << endl;

					int type; cin >> type;
					if (type == 1) CustomerMenu();
					else if (type == 2) AdminMenu();
					else if (type == 3)break;
					else {
						cout << "ERROR Invalid Input" << endl;
						continue;
					}
				}
			}
			else continue;
		}
}
}

//Login
//Register

int main() {
	readOrders();
	ReadDataForUser(); //DONE
	ReadStore();
	ReadDataForShoppingCart();
	Greeting();

	return 0;
}