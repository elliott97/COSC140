//Prime 2
//Author: Brian Lundell

#include <iostream>
#include <istream>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <vector>
#include <cmath>

using namespace std;


/*
   the isprime class has the function overloaded and the constructor in the public
   The constructor works to set the first element in the vector to the first prime, 2
   The vecto acts to hold all the prime numbers found
 */
class isprime {

	public:
		isprime() {v.push_back(2);}
		bool operator()(int & num);
	private:
		vector<int> v;
};

bool isprime::operator()(int &num) {
	//Like Prime1, this handles the 1 and negative number cases
	if(num<2)
		return false;


	/*
	   This checks to see if the last element in the vector is less than the one being tested
	   If it is true, it then works to populated the list with primes until it reaches a number
	   that is equal or greater to the number being tested. The key thing is that primes are only
	   push backed if it is a prime. So if we only had 2 in the list and tested 8, it would exit at 11
	   If the value of the number is equal to the last value in the vector, then it is a prime
	 */
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
	/*
	   This handles the case if the number being tested is less than the element at the back of the vector
	   It uses the find function at three iterators to go throught and see if that value is in the list
	   If it's not, it returns false and if it is found, it's being returned true since it is prime
	 */

	if(num<=v.back()) {
		vector<int>::iterator v1 = v.begin();
		vector<int>::iterator v2 = v.end();
		vector<int>::iterator v3;
		v3 = find(v1, v2, num);
		if(v3 == v2)
			return false;

		else return true;

	}
}

//---------------------------------------------------------------------
//INT MAIN() BELOW ME
//---------------------------------------------------------------------
int main() {

	isprime pcheck;
	int num;
	while(cin>>num) {

		if(pcheck(num))
			cout<<num<<" is a prime number \n";
	}

	return 0;
}
