#include <fstream>

using namespace std;

template <class T>
class Functor
{
public:
	T operator () (T a, T b)
	{
		return a*b;
	}
};

template <class T, template <class> class BinaryOp>
T pow (int a, int n, BinaryOp <T> x)
{
	if (n == 1)
	{
		return a;
	}
	if (n%2 == 0)
	{
		long long res = pow (a, n/2, x);
		return x(res, res);
	}
	else
	{
		return x(pow(a, n-1, x), a);
	}
}

template <class T, template <class> class BinaryOp>
T pow_stupid (int a, int n, BinaryOp <T> x)
{
	T multi = 1;
	for (int i = 0; i < n; i++)
	{
		multi *= a;
	}
	return multi;
}

int main()
{
	ifstream io ("input.txt");
	ofstream oo ("output.txt");

	int a; int n;
	io >> a >> n;

	Functor <int> f;

	if (pow(a, n, f) == pow_stupid(a, n, f))
	{
		oo << "It works!!!" << endl
			<< pow (a, n, f);
	}
	else
	{
		oo << "You make a mistake!" << endl;
	}
	return 0;
}