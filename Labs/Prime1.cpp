//Prime 1
//Author: Brian Lundell

#include <iostream>
#include <cmath>

using namespace std;

bool isprime(int num) {
	//Quick Error check to fix the issue of negative numbers and 1
	//It returns false
	if(num<2)
		return false;

	//This portion of the code goes ahead and works to check that it is a prime
	//It uses the the sqrt() function metioned in the lab handout to simplify the code
	//It starts at 2 since it would otherwise throw false positives with i=1
	//If nothing is able to give a remainder of 0, it returns true meaning prime
	else {
		for(int i=2; i<=sqrt(num); i++) {
			if(num % i == 0)
				return false;
		}
		return true;
	} }

int main() {

	int num; //int variable to hold number put into function and use in cin

	while(cin>>num) {

		if(isprime(num))
			cout<<num<<" is a prime number \n";
	}

	return 0;
}
