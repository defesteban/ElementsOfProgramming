#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


template <class cyc>
class Cycle
{
	int n;
	cyc x0;
public:
	Cycle(int _n, cyc _x0)
	{
		n = _n; x0 = _x0;
	}
	cyc First();
	cyc Second();
private:
	cyc my_function(cyc x, cyc n);
};

template <class cyc>
cyc Cycle<cyc>::my_function (cyc x, cyc n)
{
	return (x*x+37*x+7)%n;
}

template <class cyc>
cyc Cycle<cyc>::First()
{
	int in_cycle = x0;

	for (int i = 0; i < n+1; i++)
	{
		in_cycle = my_function(in_cycle, n);
	}

	int prom = my_function(in_cycle, n);
	int numb_cycle = 1;

	while (in_cycle != prom)
	{
		numb_cycle++;
		prom = my_function(prom, n);
	}

	int x = x0;
	prom = x0;
	for (int i = 0; i < numb_cycle; i++)
	{
		prom = my_function(prom, n);
	}

	int numb_pr_cycle = 0;

	while (x != prom)
	{
		x = my_function(x, n);
		prom = my_function(prom, n);
		numb_pr_cycle++;
	}
	return numb_pr_cycle;
}

template <class cyc>
cyc Cycle<cyc>::Second()
{
	vector <int> paths(n);
	paths.assign(n, -1);
	int beginning = x0;
	int k = 0;
	while (paths[beginning] == -1)
	{
		paths[beginning] = k;
		k++;
		beginning = my_function(beginning, n);
	}
	return paths[beginning];
}

int main()
{
	ifstream io ("input.txt");
	ofstream oo ("output.txt");
	int n, x0;
	io >> n >> x0;

	Cycle<int> prog(n, x0);

	if (prog.First() == prog.Second())
	{
		oo << "Answer is " << prog.Second() << endl;
	}
	else
	{
		oo << "Answer is not correct" << endl;
	}
	return 0;
}