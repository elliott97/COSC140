//Lab Four
//Author: Brian Lundell
//----------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <algorithm>

using namespace std;
typedef unsigned int uint;

//----------------------------------------------------------------
//Hash Table Class
//----------------------------------------------------------------
class hash_table {
	public:
		hash_table();
		void insert(const string &, const int &);
		const vector<int> & find(string &key);

	private:
		class key_line {
			public:
				vector<int> ln;
				string word;
				//inuse() was a simple test of the new word against the default string Constructor
				//the operator was another simple test of the value in the table and the one being tested
				bool inuse() { if(word == string()) return false; else return true; }
				bool operator==(const string & key) { return word==key; }
		};
		int hash(const string &);
		int nextprime(int);
		int qprobe(const string &);
		void resize();
		int num_inuse;
		int max_inuse;
		vector <key_line> table;
};

//----------------------------------------------------------------

//Find function
//Because of variables being destroyed, this is the best way to return the
//vector of ints back to the main function, regardless if it is empty or not
const vector<int> & hash_table::find(string &key) {
	int index = qprobe(key);
	return table.at(index).ln;
}

//Insert function
//This function gets an index value, that index value is then tested to see if
//is in use, if it isn't, the table is updated with that key value and the ln found at
//If it fails that check, it checks to see if that ln is in use, if it is, it is ignored to prevent repeats
//otherwise it is added to the vector
void hash_table::insert(const string &key, const int &ln) {
	int index = qprobe(key);
	if ( ! (table[index].inuse() ) ) {
		table[index].ln.push_back(ln);
		table[index].word = key;
		if(++num_inuse >= max_inuse) {
			resize(); }
	}
	else {
		if(std::find(table[index].ln.begin(), table[index].ln.end(), ln) == table[index].ln.end())
			table[index].ln.push_back(ln);
	}
}

//Constructor
hash_table::hash_table() {
	int N = 23;
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
}

//Hash Function
int hash_table::hash(const string & key) {
	int index = 0;
	const char *c = key.c_str();
	while(*c) {
		index = ((index << 5) | (index >> 27)) + *c++;
	}
	return ((uint)index % table.size());
}

//Next Prime Function
int hash_table::nextprime(int num) {
	int i = 2;
	while(i*i <= num) {
		if (num % i == 0) {
			num++;
			i = 1;
		}
		i++;
	}
}

//QProbe Function
int hash_table::qprobe(const string &key) {
	int index = hash(key);
	int k = 0;
	while(table[index].inuse() && table[index].word != key) {
		index += 2*(++k) - 1;
		index = index % table.size();
	}
	return index;
}

//Resize Function
//Only change was the use of inuse()
void hash_table::resize() {
	vector<key_line> tmp_table;
	for(int i = 0; i<(int)table.size(); i++) {
		if(table[i].inuse())
			tmp_table.push_back(table[i]);
	}

	//Next Prime Function
	int N = nextprime(2*table.size());
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
	for(int i = 0; i<(int)tmp_table.size(); i++) {
		key_line &key = tmp_table[i];
		table[qprobe(key.word)] = key;
		num_inuse++;
	}
}

//----------------------------------------------------------------
//INT MAIN BELOW ME
//----------------------------------------------------------------
int main(int argc, char* argv[]) {
	hash_table H;         //Hash Table Item
	string key;           //String to hold the lines in the get line function
	int ln = 1;           //Line Numbrs that
	stringstream ss;      //string stream to read from the getlines
	ifstream fin;         //File ifstream to open file
	vector<string> temp;  //This is the reference vector for the text file
	vector<int> tmpln;    // Vector of line numbers to be used in future reference with the text file
	string tmph;          //tmph is just another string to hold a temporary string
	string input;         //String input for finding items in the text file

	//Error check for correct # of arguments into the terminal
	if(argc < 2) {
		cerr<<"Less than two arguments. \n Usage: ./Hashtable newtext.txt \n";
		return -1;
	}
	//This pushes something onto the first element on the vector so the ln and index actually line up
	temp.push_back("First/0th Element");

	//Error checks to ensure the file is opened
	fin.open(argv[1]);
	if(fin.fail()) {
		cerr<<"file open failed \n";
		return -2;
	}

	//This gets the line from the file and pushes it onto the string cache
	//Since something was pushed onto the 0th index, we can get the cache from the line number directly
	//This then goes through that string to check for puncs and replaces if necessary
	while(getline(fin, key)) {
		temp.push_back(key);
		string::iterator t1 = key.begin();

		while(t1 != key.end())  {
			if(ispunct(*t1))
				*t1 = ' ';
			++t1; }

		//Using stringstream to get individual words
		//We index that word and linenumber with the insert function
		//The linenumber is then increased
		ss.clear();
		ss.str(key);

		while(ss>>tmph) {
			H.insert(tmph, ln);
		}
		ln++;

	}

	fin.close();

	//Find function
	//Endless loop to take inputs and then search for them
	cout<<"find> \n";
	while(cin>>input) {

		//Looks for the input, then checks to make sure that the vector<int> holds values
		//If not, an error is given and it is worked through again
		tmpln = H.find(input);
		if(tmpln.empty())
			cout<<"Error: Input not found \n";


		//Then using the the returned vector, this will go through and print out the
		//line number from the found values using the string cache
		else {
			for(int i = 0; i<tmpln.size(); i++) {
				cout<<setw(4)<<tmpln.at(i)<< " : ";
				cout<< temp.at(tmpln.at(i));
				cout<<"  \n";
			} }
		cout<<"find> \n";
	}

}

//----------------------------------------------------------------
