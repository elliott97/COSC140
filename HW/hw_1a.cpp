//
//Author: Brian Lundell
//HW 1a
//

#include <iostream>
#include <iomanip>

using namespace std;


int main(int argc, char *argv[]) {

cout<< "Num args = "<< argc<<"\n";

for(int i=0; i<argc; i++) {

cout<<"argv["<<i<<"] = " << &argv[i]<<"\n";

}



  return 0;
}
