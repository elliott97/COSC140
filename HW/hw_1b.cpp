//
//Author: Brian Lundell
//HW 1a
//

#include <iostream>
#include <iomanip>

using namespace std;

int strlen(const char *tmp) {

int count=0;

while(true) {

if((*tmp)=='\0') {
  break;
}

count++;
tmp++;

}
return count;

}

int main(int argc, char *argv[]) {



cout<< "Num args = "<< argc<<"\n";
int temp=0;
for(int i=0; i<argc; i++) {


temp=strlen(argv[i]);

cout<<"argv["<<i<<"] = " << &argv[i]<<" "<<argv[i]<<" "<<"(strlen="<<temp<<")"<<
"\n";

}



  return 0;
}
