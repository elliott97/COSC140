#include <cstdlib>
#include <iostream>
#include <sstream> //Using sstream to gather the values of the card
#include <iomanip> //iomanip for formatting the output

using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
	"8", "9", "10", "Jack", "Queen", "King" };
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

string random_card(bool verbose=false) {
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
		cout << card << "\n";

	return card;
}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	string rank; //Set of strings to hold the values of the returned card
	string of;
	string suitss;
	stringstream ss;
	int broken; //Broken is used to find the row where all the suits are found, use for the ** format
	int ranks; //suits and ranks is used for setting the count of all cards in the deck
	int suits;

	for (int i=1; i<argc; i++) {
		string option = argv[i];
		if (option.compare(0,6,"-seed=") == 0) {
			seedvalue = atoi(&argv[i][6]);
		} else if (option.compare("-verbose") == 0) {
			verbose = true;
		} else
			cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue);

	int deck[4][13] = {}; //static deck with 52 spots in row*column fashion
	// declare a table called deck that keeps track of
	// card faces dealt for each suit -- initialize to 0

	while (1) {
		string card = random_card(verbose);

		//Using stringstream to read the words of the string
		//clear() is used to reset the flags of ss to read in another card
		ss.clear();
		ss<<card;
		ss>>rank>>of>>suitss;

		//These two blocks read to find a matching card in the global strings above
		//it then sets an integer to set the count of the number of cards counted
		for(int i=0; i<13; i++) {
			if(rank == face[i])
				ranks = i;
		}
		for(int j=0; j<4; j++) {
			if(suitss == suit[j])
				suits = j;
		}

		//increases the specific card count by one
		deck[suits][ranks]++;

		//Series of if statements to check if the last three face cards (jack, queen, king) are found
		//for each suit
		//if a suit has above one for all of these, all face cards in that suit has been found
		//it then sets the integer broken to row that it found all cards to be used in the formatting
		if(deck[0][10]>0)
			if(deck[0][11]>0)
				if(deck[0][12]>0) {
					broken = 0;
					break; }

		if(deck[1][10]>0)
			if(deck[1][12]>0)
				if(deck[1][12]>0) {
					broken = 1;
					break; }

		if(deck[2][10]>0)
			if(deck[2][11]>0)
				if(deck[2][12]>0) {
					broken = 2;
					break; }

		if(deck[3][10]>0)
			if(deck[3][11]>0)
				if(deck[3][12]>0) {
					broken = 3;
					break; }




		// reverse engineer card suit and face

		// break out of loop if stopping criteria met
	}

	//This block prints out the deck
	//If it is the row which contained all the break cards, it checks it in the if statement
	//It checks to make sure that the row is the one set to broken and that it is at the end of the
	// the columns, if all true, it prints out the **
	for(int i=0; i<4; i++){
		cout<<setw(8)<<suit[i]<<": ";
		for(int j=0; j<13; j++) {
			cout<<setw(4)<<deck[i][j];
			if(i==broken && j==12)
				cout<<" **";
		}
		cout<<"\n";
	}
	// print formatted table contents to stdout
}
