//
//Author: Brian Lundell
//Lab1 Prog1d
//

//This is a lot of libraries
//cpp.com mentions string, cctype, and locale when using isupper, isalpha, islower
//I'll just include them all to be safe
#include <iostream>
#include <string>
#include <locale>
#include <cctype>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;

void enc(string &tmp, int key) {
	//This for loop will go through the string
	//Checks to see if it's a letter and modifies it if it is
	//Uses isupper and islower to check the bounds of it
	//Both isupper and islower check to see if it exceeds the bound of the alphabet
	char tmpchar;
	for(int i=0; i<tmp.length(); i++) {

		tmpchar = tmp[i];

		if(isalpha(tmpchar)) {
			if(isupper(tmpchar)) {

				tmpchar = (tmpchar)+key;
				if(tmpchar>90) {

					tmpchar = tmpchar-26;
				}
				tmp[i] = tmpchar;
			}

			else if(islower(tmpchar)) {
				tmpchar+=key;
				if(tmpchar>122) {
					tmpchar = tmpchar-26;
				}
				tmp[i]=tmpchar;
			}
		} // end of isslpha

	} // end of for loop
	cout<<tmp<<"\n";
}

void dec(string &tmp, int key) {
	//This for loop will go through the string
	//Checks to see if it's a letter and modifies it if it is
	//Uses isupper and islower to check the bounds of it
	//Both of isupper and islower check to see if it exceeds the bounds of the alphabet
	char tmpchar;

	for(int i=0; i<tmp.length(); i++) {

		tmpchar = tmp[i];

		if(isalpha(tmpchar)) {
			if(isupper(tmpchar)) {

				tmpchar = (tmpchar)-key;
				if(tmpchar<65) {
					tmpchar += 26;
				}
				tmp[i]=tmpchar;
			}

			else if(islower(tmpchar)) {
				tmpchar = (tmpchar) -key;
				if(tmpchar<97) {
					tmpchar += 26;
				}
				tmp[i]=tmpchar;
			}
		} // end of isslpha

	} // end of for loop

	cout<<tmp<<"\n";
}


int main(int argc, char *argv[]) {


	//Error check for correct number of arguments
	if(argc!=3) {
		cerr<< "Not enough args"<<"\n";
		return 1;
	}

	//three variables
	// cmd is either decode or encode, key is the third argument
	string cmd = argv[1];
	int key = atoi(argv[2]); //Converts argv[2] to an integer
	string msg;

	//Converts this to a proper string to compare it later down the code
	cmd = (string(cmd));

	//Quick error check to make sure the cmd is actually a correct command
	if(cmd != "-encode") {
		if(cmd != "-decode") {
			cerr<<"First command should be ""-encode"" or ""-decode"""<<"\n";
			return 3;
		}
	}


	//Error checking for correct key value (0-9)
	if(key>9 || key<0) {
		cerr<<"Invalid key"<<"\n";
		return 2; }

	//uses get line to get the message to be encoded or decoded
	getline(cin, msg);


	//Simple if statement on which function to exeute depending on cmd
	if(cmd == "-encode") {
		enc(msg, key); }

	else if(cmd == "-decode") {
		dec(msg, key); }

	return 0;
}
