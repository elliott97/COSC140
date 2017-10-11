/*
Author: Brian Lundell
HW 5
 */

#include <iostream>

using namespace std;

/*
   Template class of the stats
   Min and Max have been removed
   Sum has been initialized to non data specific "0" & N set to 0

 */

template <typename T>
class stats {
	public:
		void push(T &v);
		void print();
		stats();

	private:
		int N;
		T sum;
};

template <typename T>
stats<T>::stats() {
	N = 0;
	sum = T();
}

template <typename T>
void stats<T>::push(T &v) {
	sum+=v;
	N++;
}

template <typename T>
void stats<T>::print() {
	cout<<"N = "<<N<<"\n";
	cout<<"sum = "<<sum<<"\n";
}


int main() {

	//This is my pretty garbage test code
	//It works given you follow the instructions
	//Also need to rerun the program to test it again.
	stats<int> s;
	stats<float> v;
	stats<string> k;

	char code;
	int intest1, intest2, intest3;
	float floattest1, floattest2, floattest3;
	string stest1, stest2, stest3;

	cout<<"Test Codes:"<<"\n";
	cout<<"Int: I"<<"\n"
		<<"Float: F"<<"\n"
		<<"String: S"<<"\n";

	cin>>code;
	cout<<"Enter Three Values:\n";

	if(code=='I') {
		cin>>intest1>>intest2>>intest3;
		s.push(intest1);
		s.push(intest2);
		s.push(intest3);
		s.print();
	}

	if(code=='F') {
		cin>>floattest1>>floattest2>>floattest3;
		v.push(floattest1);
		v.push(floattest2);
		v.push(floattest3);
		v.print();
	}

	if(code=='S') {
		cin>>stest1>>stest2>>stest3;
		k.push(stest1);
		k.push(stest2);
		k.push(stest3);
		k.print();
	}


	return 0;
}
