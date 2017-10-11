//Prime 3
//Author: Brian Lundell
//Comments were probably left out from Prime 1 and Prime 2

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

class isprime {
	public:
		isprime() {v.push_back(2);}
		bool operator()(int & num);
	private:
		vector<int> v;
};

bool isprime::operator()(int &num) {

	if(num<2)
		return false;

	if(num>v.back()) {
		int temp = v.back();
		while(num>v.back()) {
			bool tmp = true;

			for(int i=2; i<=sqrt(temp); i++) {
				if((temp % i == 0)) {
					tmp = false;
				}
			}
			if(tmp)
				v.push_back(temp);
			temp++;
		}

		if(num==v.back())
			return true;

		else return false;

	}
  //Only part of Prime3 that has changed here is this function which is binary_search()
  //instead of find()
  //if foundyn is set to true, that means it was found in the list and that number is prime
	if(num<=v.back()) {
		vector<int>::iterator v1 = v.begin();
		vector<int>::iterator v2 = v.end();
		bool foundyn = false;
		foundyn = binary_search(v1, v2, num);
		if(foundyn)
			return true;

		else return false;

	}
}


//Simple function to get random numbers between 1-100
//the plus 1 is to fix the issue of getting a 0-99
int NumGen() {return (rand() % 100) + 1;}

//---------------------------------------------------------------------
//INT MAIN() BELOW ME
//---------------------------------------------------------------------
int main(int argc, char* argv[]) {

	isprime pcheck; //class to use for future use
	int countn; //countn is used to hold the values of the count() function
	int N; //Seed/argument value
  //The simple error check incase there are not arguments given
  if(argc<2)
  N = 10;

//Converts the command line argument into a digit and sets that equal to N
  else N = atoi(argv[1]);

//Then seeds srand with N
  srand(N);
	vector<int> templist; //int vector to hold values that need to be checked with item
	vector<bool> boolvec; //Bool vector to hold true or false and aligns with tempList

//Resizes the two arrays to size N to stop once that size has been met
templist.resize(N);
boolvec.resize(N);

//Declaration of the iterators to use for future reference
vector<int>::iterator t1 = templist.begin();
vector<int>::iterator t2 = templist.end();
vector<bool>::iterator b1 = boolvec.begin();
vector<bool>::iterator b2  = boolvec.end();

//Generates the list of numbers of to use in the vector, uses the generate function
//Passes the function NumGen to populate the list
generate(t1, t2, NumGen);

//Re-assigns the t1 to the beginning of the the vector again
t1 = templist.begin();

//Uses transform to populate the bool vector to either be true or false
transform(t1, t2, b1, pcheck);

//Re-assigns the value of b1 to the beginning of the bool list again
b1 = boolvec.begin();

//Uses the count function to find the number of trues in the list
countn = count(b1, b2, true);

//Prints out the amount of primes found
cout<<"Sequence contains "<<countn<<" prime numbers. \n";

	return 0;
}
