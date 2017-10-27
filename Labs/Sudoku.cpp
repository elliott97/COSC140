//Author: Brian Lundell
//Lab 5
//------------------------------------------------------------------
//**Sorry about the mess of this code, Lab Six will be way better

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class sudoku {
	public:
		sudoku();

		void solve();

		void read(const char *);
		void write(const char *);
		void write(const char *, const char *);

	private:
		bool solve(int, int); // arguments not int

		// various support functions
		bool error_check_value(int, int, int);
		bool error_check_index(int, int, int);
		bool error_check_uniqueness();
		vector<int> valid_values(int, int);

		void display();

		int game[9][9];
};

sudoku::sudoku() {
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++)
			game[i][j] = 0;
	}
}

//Valid Values Function
vector<int> sudoku::valid_values(int row, int col) {
	vector<int> master;
	for(int y = 1; y < 10; y++) {
		master.push_back(y);
	}
	vector<int>::iterator m;


	//Grid
	for(int i = (row/3)*3; i < ((row/3)*3)+3; i++) {
		for(int j = (col/3)*3; j < ((col/3)*3)+3; j++) {
			if(game[i][j] != 0) {
				m = find(master.begin(), master.end(), game[i][j]);
				if(m != master.end())
					master.erase(m);

			}
		}
	}

	//Check Row
	for(int k = 0; k < 9; k++) {
		if(game[row][k] != 0) {
			m = find(master.begin(), master.end(), game[row][k]);
			if(m != master.end())
				master.erase(m);
		}
	}


	//Check Column
	for(int k = 0; k < 9; k++) {
		if(game[k][col] != 0) {
			m = find(master.begin(), master.end(), game[k][col]);
			if(m != master.end())
				master.erase(m);
		}
	}
	return master;
}

void sudoku::solve() {
	cout << "SOLVE\n";
	int row = 0;
	int col = 0;
	// call recursive computation
	//This gets the bool value of the solve function
	//It then displays the game board and then if the game failed, it prints out that it failed.
	bool success;
	success = solve(row,col);

	display();

	//Using two values, an int and a false bool
	//The int is used to hold the value
	bool solved1 = false;
	bool solved2 = error_check_uniqueness();
	//This checks quickly to see if the non uniqueness is met and if it is not
	//the program is terminated
	if(!(solved2)) {
		exit(-1);
	}

	//This quick check is used for the when the the recursion fails and not due to uniqueness
	if(!(success)) {
		cerr<<"Error: Not Solved \n";
		exit(-1);
	}


	//This is a counter to check for the proper value in the game board
	int wrong1 = 0;

	//Using an int to increment in case the values are not between 1-9
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			solved1 = error_check_value(1, 9, game[i][j]);

			if(solved1)
				wrong1++;
		}
	}

	//This is the exiting if either value functions throws an error
	if(wrong1 != 0) {
		exit(-1);
	}

}

//Error Check index
//Simple check of making sure the index value is within the range of the grid
//If it is within the bounds, false gets returned meaning the index is good
bool sudoku::error_check_index(int row, int col, int val) {
	bool tru1 = true;
	bool tru2 = true;
	int min = 0;
	int max = 8;
	if(row < min || row > max)
		tru1 = false;

	if(col < min || col > max)
		tru2 = false;

	if(tru1 && tru2)
		return false;

	else {
		cerr<<row<<" "<<col<<" "<<val<<" Illegal Grid Index"<<"\n";
		return true;
	}
}

//Error Check Value
//A simple value check making sure the values put in the board are between 1-9
bool sudoku::error_check_value(int min, int max, int val) {
	if(val < min || val > max) {
		cerr<<"Error in Value: "<<val<<"\n";
		return false;
	}

	else return true;
}

//Error Check Unique
//This uses a system of three bools to go through the entire board checking
//the row, then the columns, then the grids
//The row and column checking is self explanatory essentially. I'll comment
//on the grid below
bool sudoku::error_check_uniqueness() {
	bool tru1 = true;
	bool tru2 = true;
	bool tru3 = true;
	bool printedyn = false;

	//Two main for loops to loop through the game board
	//Within these two for loops are more for loops to go through the row, col, then the grid
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
		//printedyn is used to check the to see if that item has been printed for game[i][j]
		//if it has been printed, it goes ahead and skips printing out the repeated value
			printedyn = false;


			//Check Row
			for(int k = 0; k < 9; k++) {
				if(game[i][j] == game[i][k] && !(game[i][j] == 0) && j != k && !(printedyn)) {
					cerr<<i<<" "<<j<<" "<<game[i][j]<<" Illegal non-unique value \n";
					tru1 = false;
					printedyn = true;
				}

			}

	//Check Column
			for(int l = 0; l < 9; l++) {
				if(game[i][j] == game[l][j] && !(game[i][j] == 0) && i != l && !(printedyn)) {
					cerr<<i<<" "<<j<<" "<<game[i][j]<<" Illegal non-unique value \n";
				tru2 = false;
				printedyn = true;
			}
			}

	//Checking the grid uses mod remainders to set the bounds
	//The code can be condensed down, but for the sake of seeing what's happening
	//I'm going to leave it long and open like this
	//It works by getting the remainder of the iteration, subtracting that remainder
	//that acts as the lower bound. The upper bound is simply lower plus 3
	//This then goes through another two for loops that check the grid against the grid values
	//Check Grid
			int rw = i % 3;
			int cw = j % 3;
			int in = i - rw;
			int jn = j - cw;
			int im = in + 3;
			int jm = jn + 3;
			for(in; in < im; in++) {
				for(jn; jn < jm; jn++) {
					if(game[in][jn] == game[i][j] && !(game[in][jn]) == 0 && jn != j && in != i && !(printedyn)) {
						tru3 = false;
						printedyn = true;
						cerr<<in<<" "<<jn<<" "<<game[in][jn]<<" Illegal non-unique value \n";
					}

				}
			}
		}
	}

	//If all three items are true, then this executes and true is returned
	if(tru1 && tru2 && tru3)
		return true;

	else return false;
}

void sudoku::read(const char *fname) {
	cout << "READ\n";

	ifstream fin(fname);

	int i, j, v;
	bool tmp1;
	bool tmp2;
	int wrong1 = 0;
	int wrong2 = 0;

	while (fin >> i >> j >> v) {
		// error check grid indice
		tmp1 = error_check_index(i, j, v);
		if(tmp1)
			wrong1++;

		bool success1 =

			tmp2 = error_check_value(0, 9, v);
		if(!(tmp2)) {
			wrong2++;
			cerr<<"Invalid Index: "<<i<<" "<<j<<" "<<v<<" \n";
		}

		if(!(tmp1))
			game[i][j] = v;
	}

	fin.close();

	// exit if bad grid indices
	if(wrong1 != 0)
		exit(-1);
	// error check data values
	if(wrong2 != 0)
		exit(-2);

	display();


	// error check uniqueness
	bool success = error_check_uniqueness();
	if(!(success))
	exit(-1);
	// exit if errors detected
}


//Do Not Change
void sudoku::write(const char *fname) {
	ofstream fout(fname);

	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (0 < game[i][j]) {
				fout << i << " "
					<< j << " "
					<< game[i][j] << "\n";
			}
		}
	}

	fout.close();
}

//Do Not Change
void sudoku::write(const char *fname, const char *addon) {
	int N1 = strlen(fname);
	int N2 = strlen(addon);

	char *n_fname = new char[N1+N2+2];

	// strip .txt suffix, then concatenate _addon.txt
	strncpy(n_fname, fname, N1-4);
	strcpy(n_fname+N1-4, "_");
	strcpy(n_fname+N1-3, addon);
	strcpy(n_fname+N1-3+N2, ".txt");

	write(n_fname);

	delete [] n_fname;
}

void sudoku::display() {
	cout << "| ----------------------------- |\n";
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (j%3 == 0)
				cout << "|";
			cout << "  " << game[i][j];
		}
		cout << "  |\n";
		if (i%3 == 2)
			cout << "| ----------------------------- |\n";
	}
}

bool sudoku::solve(int row, int col) {

	//This exits the recursion just in case the recursion goes outside
	//the bounds of the game board
	if(row == 9)
		return true;

	//This gets the vector of valid values specific for this row, col
	vector<int> m = valid_values(row, col);

	//This just checks if the last index is set and if it is, it'll exit successfully
	if(row == 8 && col == 8 && game[8][8] != 0)
		return true;

	//Similar to the check above, this checks the if the last item is not set, and
	//goes ahead to set it to the last valid value from the vector and exits successfully
	if(row == 8 && col == 8 && m.size() == 1) {
		game[row][col] = m.at(0);
		return true;
	}

	//This is the case if the index on the game[][] is already set
	//It then goes ahead to move on and recursion the next solution
	//Simple recursion, working with columns first and then the rows
	//This checks to see if the recursion returns true and if it is, true is returned
	//Else, false is returned
	if(game[row][col] != 0) {
		if(col < 8) {
			if(solve(row, col+1))
				return true; }

		else {
			int ncol = 0;
			if(solve(row + 1, ncol))
				return true;
		}
		return false;
	}


	//Bit of a redundant check but it's neat so I'm leaving it in
	//This is when the game board is not set
	//It then goes through the vector checking all possible valid values
	//It functions the same way with the recursion above, the key difference
	//is setting the board and resetting the board
	//If the recursion gets returned false, we try another value in the vector
	//and then we work down the branching again
	if(game[row][col] == 0) {

		for(int k = 0; k < m.size(); k++) {
			game[row][col] = m.at(k);

			if(col < 8) {
				if(solve(row, col + 1))
					return true;
			}
			else {
				int ncol = 0;
				if(solve(row + 1, ncol))
					return true;
			}
			game[row][col] = 0; //Reset

		}
		return false;

	}
}
int main(int argc, char *argv[]) {
	srand(time(NULL));

	if ((argc != 3) ||
			(strcmp(argv[1], "-s") != 0) ||
			strstr(argv[argc-1], ".txt") == NULL) {
		cerr << "usage: Sudoku -s game.txt\n";
		exit(0);
	}

	sudoku sudoku_game;

	if (strcmp(argv[1], "-s") == 0) {
		sudoku_game.read(argv[2]);
		sudoku_game.solve();
		sudoku_game.write(argv[2], "solved");
	}
}
