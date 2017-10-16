//HW 9
//Author Brian Lundell

//Part 1

#include <iostream>
#include <cstdlib>
using namespace std;

int factorial(int n) {
  if(n < 0)
  return n;

  int mul;
  if(n != 1) {
    mul = n * factorial(n-1);
  }
  return mul;
}


int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  int factorial_n = factorial(n);
  cout<<"factorial = "<< factorial_n << "\n";

return 0;
}

//Part 2

/*
The magic function works through until it reaches a new line
Since it works through each word going from the start to beginning, it ends at
the end of the word, so when it begins to print out, it is at the end of the word
which causes the word to be printed in reverse.
*/
