#include	<iostream>
#include	<list>
using	namespace	std;

template <typename T>
class neq {
	public:
		neq(const T & n_target = T()) { target = n_target; }
		bool operator()(const T &v) {return v != target;}

	private:
		T target;
};

template <typename T1, typename Function>
int count( T1 v1, T1 v2, Function iseq) {
	int c = 0;
	while(v1 != v2) {
		if(iseq(*v1))
			c++;

		++v1;
	}
	return c;
}


int	main(int	argc,	char	*argv[])	{
	list<int>	v;
	list<int>::iterator	iv;
	int	value,	target;
	while	(cin	>>	value)
		v.push_back(value);
	cin.clear();
	cout	<<	"Set	target	";
	cin	>>	target;
	int	N	=	count(v.begin(),	v.end(),	neq<int>(target));
	cout	<<	"Found	"	<<	N	<<	"	elements	not	equal	to	target\n";
}
