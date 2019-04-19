#include "user.h"
#include <regex>
#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#include<map>
#include <fstream>
#include <sstream>

using namespace std;


user::user()
{
	valid = 0;
}


user::~user()
{
}
bool is_email_valid(const string& email)
{
	// define a regular expression
	const regex pattern
	("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	// try to match the string with the regular expression
	return regex_match(email, pattern);
}
// Registration function
void user::regist(map <string, user>&p) {
	cout << "Please Enter Your Email : "; cin >> email;
	if (is_email_valid(email)) {
		if (p[email].valid == 1) {
			cout << "You Have An Account Already ^^ !" << endl;
			return;
		}
		else {
			cout << "Please Enter User Name : ";
			cin >> username;
			cout << "Please Enter Password : ";
			cin >> password;
			p[email].username = username;
			p[email].password = password;
			p[email].cach = 0;
			p[email].valid = 1;
			cout << endl << endl << "                                          You Have An Account Now " << endl << endl;
		}
		//update the file after adding a user
		ofstream Wfile("dataT.txt", ios::app);
		if (Wfile.is_open()) {
			Wfile << email << " " << p[email].username << " " << p[email].password << " " << p[email].cach << endl;
		}
		Wfile.close();
	}
	else cout << "Sorry!!! Please Enter Valid Email ^^ \n";
}

//login function
string user::login(map<string, user>p)
{
	string mail, pass;
	cout << "Please Enter Your Email : "; cin >> mail;
	cout << "Please Enter Password : "; cin >> pass;
	if (p[mail].valid == 1 && p[mail].password == pass) {
		cout << endl << "                                                 Welcome " << p[mail].username << endl << endl;
		return mail;
	}
	else if (p[mail].valid == 0 || p[mail].password != pass) {
		cout << "INVALID USER YOU DONOT HAVE AN ACCOUNT" << endl;
		return "no";
	}
}
  