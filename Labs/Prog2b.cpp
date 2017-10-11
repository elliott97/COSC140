/*
Author: Brian Lundell
Program 2b
 */
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

//List class. Includes definitions for node constructors
//node struct contains the int data index and the pointer next

class list {
	public:
		struct node {
			node(int &dta) {data=dta; next=NULL;} //Creates a new node, sets the data to the value passed to it
			node() {data = 0; next=NULL;} //Creates the head node since it doesn't get a value
			int data;
			node *next;
		};

		void insert(int );
		list();
		~list();
	private:
		node *head;
		friend ostream & operator<<(ostream &, const list &);
};

//Creates a new list with only a head node
list::list() {
	head = new node;
}

//This deletes all the nodes of a list
list::~list() {
	node *p = head->next;
	node *pp;

	delete head;

	while(!(p==NULL)) {
		pp = p;
		p = p->next;
		delete pp;
	}
	delete p;
}



int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	list v[4]; //Array of lists, 4 used statically for the four card suits
	string rank; //Set of strings to hold the values of the returned card
	string of;
	string suits;
	stringstream ss;
	int index; //Index integer value that is passed to insert func. Index corresponds
	//with global array (eq index==0==Ace and index==12==King)
	int suis; //suis is the number for the suit value of the global array. Used for the deck increment and insert function
	int broken; //Bool variable for continuing the while loop
	int deck[4][13] = {}; //Static deck to use for checking

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



	while (1) {
		string card = random_card(verbose);

		//Using stringstream to read the words of the string
		//clear() is used to reset the flags of ss to read in another card
		ss.clear();
		ss<<card;
		ss>>rank>>of>>suits;


		// Simple for loop to check the face of the card generated, sets the index to that number
		for(int i=0; i<13; i++) {
			if(face[i]==rank)
				index=i;

		}
		for(int j=0; j<4; j++) {
			if (suit[j]==suits)
				suis=j;
		}

		//Calls the insert function of the v[] Array
		v[suis].insert(index);


		//This uses the same old check from Prog2a to see if all three face Cards
		//have been called. Uses the big blocks of if statements to check all the items
		// if all is true for an element, it breaks out of the loop
		deck[suis][index]++;

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



	} //End of While Loop

	// print formatted table contents to stdout
	for(int k=0; k<4; k++) {

		cout<<setw(8)<<suit[k]<<": "<<v[k];

		//This checks for the broken condition to print out the **
		if(broken==k)
			cout<<" **";

		cout<<"\n";
	}
} //End int main()

//Insert Function
void list::insert(int index) {

	/*error check so that the p->next loop will work
	  This works by working through the loop using p and pr | p is current and pr is previous
	  this checks the index to the data and if it does exist, it places the the node at the front
	  If it reaches the end of the list it creates a new node at the end of the list
	  Return is used to break out of the insert function if it has done it's purpose

	 */

	//Quick error check incase there is no elements in the list
	//If it's true, it creates a new node for that
	if(head->next==NULL) {
		node *ne  = new node(index);
		head->next=ne;
		return; }

	node *p;
	p = head->next;
	node *pr;
	pr = head;

	while(!(p->next==NULL)) {

		if(index == p->data){

			node *temp1;
			node *temp2;

			temp2=p->next;
			pr->next = temp2;

			temp1 = head->next;
			head->next = p;
			p->next = temp1;

			return;
		}
		pr=pr->next;
		p=p->next;

	}

	if(p->next==NULL) {
		p->next = new node(index);
		return;
	}


}

/*
   Definition of the ostream << operator
   Uses the node p to go through the list until the null terminator is reached
   It is attempted to format correctly but it is off a little
	 Using int i is a bit wasteful, but I enjoy using i a lot more than p->data
 */
ostream & operator<<(ostream & out, const list & v) {

	list::node *p;
	p = v.head->next;
	int i;
	while(!(p==NULL)) {
		i = p->data;
		out<<" "<<face[i]<< " ";
		p=p->next;
	}

	return out;
}
