//
//Author: Brian Lundell
//Lab1 Prog1c
//

#include <iomanip>
#include <iostream>

using namespace std;

class stats {
	public:
		void push(int);
		void print();
		stats();

	private:
		int count;
		int min;
		int max;
		int sum;
};

void stats::push(int inp) {

//Essentially same as before in 1b but not in push function
//changed N to count

	sum+=inp;

	if(count==0){
	min= inp;
	max= inp;
	}
	
	if((min-inp)>0)
		min=inp;
	if((max-inp)<0)
		max=inp;

	count++;
}

void stats::print() {
cout<<"N = "<<count<<"\n"
	<<"sum = "<<sum<<"\n"
	<<"min = "<<min<<"\n"
	<<"max = "<<max<<"\n";
}

//Used to initialize values of the class to 0
stats::stats() {
count=0;
min=0;
max=0;
sum=0;
}

int main(int argc, char *argv[]) {


stats test;
int temp;

while(cin>>temp) {

	test.push(temp);
}

test.print();


return 0;
}
