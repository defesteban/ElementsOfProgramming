#include <fstream>
#include <vector>
using namespace std;

template <class T>
class Functor
{
public:
	T operator () (T a, T b)
	{
		T c(2, 2);
		c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];
		c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];
		c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];
		c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];
		return c;
	}
};

template <class T, template <class> class BinaryOp>
T pow (T a, int n, BinaryOp <T> x)
{
	if (n == 1)
	{
		return a;
	}
	if (n%2 == 0)
	{
		T res = pow (a, n/2, x);
		return x(res, res);
	}
	else
	{
		return x(pow(a, n-1, x), a);
	}
}

int fibonacci (int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return fibonacci(n-1)+fibonacci(n-2);

}

int main()
{
	ifstream io ("input.txt");
	ofstream oo ("output.txt");

	vector <vector <int> > a(2, 2);
	a[0][0] = 1; a[0][1] = 1; a[1][0] = 1; a[1][1] = 0;
	int n;
	io >> n;

	Functor <vector <vector <int> > > f;

	vector <vector <int> > c(2, 2);
	c = pow (a, n+1, f);
	if (c[1][1] == fibonacci(n))
	{
		oo << "It works!!!" << endl << c[1][1];
	}
	else
	{
		oo << "You make a mistake!" << endl;
	}
	return 0;
}