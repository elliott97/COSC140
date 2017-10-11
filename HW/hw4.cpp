//
//Author: Brian Lundell
//HW 4
//Problem 1

class stack {
	public:
		stack();
		~stack();

		bool empty() const;
		void push(const int &din);
		void pop();
		int top();
		int size();

	private:
		int *p; //Stack Pointer
		int v[]; //integer array
		int N; //Counter, tells what elements are in the array
}

stack::stack() {
	p = new v[10] = {};
	N = 0;
}

stack::~stack() {
	delete [] p;
}


bool stack::empty() const {
	if(N==0)
		return true;

	else
		return false;
}

int stack::size() const {
	return N;
}

void stack::push(const int &din) {
	v[N] = din;
	p++;
	N++;
}

}
void stack::pop() {
	p--;
	N--;
}


int stack::top() {
	return *p;
}


//Problem 2:
// Error Checks in pop(): not allowing a pop to occur when N=0 to avoid popping garbage
//

//Error Checks in push(): Have a case to warn if the user is pushing onto a full array
//

//Error Checks in top(): Similar to pop(), not allow a top() when the N=0.
//
