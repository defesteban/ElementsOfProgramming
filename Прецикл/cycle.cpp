#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;

template <class Object>
class Transformation
{
public:
	Object virtual operator() (const Object& object) const = 0;
};

template <class T>
class MyTransformation : Transformation <T>
{
public:
	MyTransformation (int domain) : domain_ (domain) { }
	T operator()(const int& x) const
	{
		T prom = (x*x + x) % domain_;
		return prom;
	}
	int domain() const
	{
		return domain_;
	}
private:
	int domain_;
};

template <class cyc, template<class> class A>
class PreCycleLengthFinder
{
	cyc x0;
	const A<cyc>& transformation;
public:
	PreCycleLengthFinder(cyc _x0, const A<cyc>& _transformation) : transformation (_transformation)
	{
		x0 = _x0;
	}
	void tester(PreCycleLengthFinder prog, ofstream& oo);
	private:
	cyc fastPrecycleLength();
	cyc precycleLength();
};

template <class cyc, template<class> class A>
cyc PreCycleLengthFinder<cyc, A>::fastPrecycleLength()
{
	int n = transformation.domain();
	int element_in_cycle = x0;

	for (int i = 0; i < n+1; i++)
	{
		element_in_cycle = transformation(element_in_cycle);
	}

	int prom = transformation(element_in_cycle);
	int numb_cycle = 1;

	while (element_in_cycle != prom)
	{
		numb_cycle++;
		prom = transformation(prom);
	}

	int x = x0;
	prom = x0;
	for (int i = 0; i < numb_cycle; i++)
	{
		prom = transformation(prom);
	}

	int numb_pr_cycle = 0;

	while (x != prom)
	{
		x = transformation(x);
		prom = transformation(prom);
		numb_pr_cycle++;
	}
	return numb_pr_cycle;
}

template <class cyc, template<class> class A>
cyc PreCycleLengthFinder<cyc, A>::precycleLength()
{
	int n = transformation.domain();
	vector <int> paths(n);
	paths.assign(n, -1);
	int beginning = x0;
	int k = 0;
	while (paths[beginning] == -1)
	{
		paths[beginning] = k;
		k++;
		beginning = transformation(beginning);
	}
	return paths[beginning];
}

template <class cyc, template<class> class A>
void PreCycleLengthFinder<cyc, A>::tester(PreCycleLengthFinder<cyc, A> prog, ofstream& oo)
{
	assert(prog.fastPrecycleLength() == prog.precycleLength());
		oo << "Answer is " << prog.precycleLength() << endl;
}

int main()
{
	ifstream io ("input.txt");
	ofstream oo ("output.txt");
	int n, x0;
	io >> n >> x0;
		
	MyTransformation <int> transformation(n);
	PreCycleLengthFinder<int, MyTransformation> prog(x0, transformation);
		
	prog.tester(prog, oo);

	return 0;
}