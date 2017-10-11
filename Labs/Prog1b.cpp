//
//Author: Brian Lundell
//Lab1 Prog1b
//

#include <iomanip>
#include <iostream>


using namespace std;


int main(int argc, char *argv[]) {

int min;
int max;
int N=0;
int sum=0;
int temp;

//While loop adding sum and getting count and finding min/max
while(cin>>temp) {
sum+=temp;
//Sets the first value to use for the min/max then moves on
if(N==0) {
	min=temp;
	max=temp;
}


//Simple checking for min or max using temp file
if((min-temp)>0)
	min=temp;

if((max-temp)<0)
	max=temp;

N++;

}


//Print all items for the stats
cout<< "N = "<< N << "\n"
<<"sum = "<<sum<<"\n"
<<"min = "<<min<<"\n"
<<"max = "<<max<<"\n";

return 0;
}
