#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>

using namespace std;

//================================ÊËÀÑÑ ÄÐÎÁÈ====================================================

class Fraction
{
	int numerator;
	int denominator;
public:
	Fraction()
	{
		numerator = 0;
		denominator = 1;
	}
	Fraction(int numerator_, int denominator_)
	{
		numerator = numerator_;
		denominator = denominator_;
		balancing();
	}
	Fraction(int numerator_)
	{
		numerator = numerator_;
		denominator = 1;
	}
	Fraction(const Fraction& shot)
	{
		numerator = shot.getNumerator();
		denominator = shot.getDenominator();
	}
	int getNumerator() const
	{
		return numerator;
	}
	int getDenominator() const
	{
		return denominator;
	}

	Fraction balancing();
	Fraction operator = (Fraction shot);
	Fraction operator = (int number);
	bool operator == (Fraction& shot);
	bool operator == (int number);
	bool operator != (Fraction& shot);
	bool operator != (int number);
	Fraction operator + (Fraction& shot) const;
	Fraction operator + (int number) const;
	Fraction operator - (Fraction& shot) const;
	Fraction operator - (int number) const;
	Fraction operator * (Fraction& shot) const;
	Fraction operator * (int number) const;
	Fraction operator / (Fraction& shot) const;
	Fraction operator / (int number) const;
	bool operator > (Fraction& shot);
	bool operator > (int number);
	bool operator < (Fraction& shot);
	bool operator < (int number);
	bool operator >= (Fraction& shot);
	bool operator >= (int number);
	bool operator <= (Fraction& shot);
	bool operator <= (int number);
	bool isInt() const;
};

Fraction Fraction::balancing()
{
	if (numerator == 0)
	{
		denominator = 1;
		return *this;
	}

	int numerator_;
	int denominator_;
	int divider;
	if (numerator < 0)
		numerator_ = numerator;
	else
		numerator_ = -numerator;
	if (denominator < 0)
		denominator_ = denominator;
	else
		denominator_ = -denominator;
	if (numerator > denominator)
		divider = numerator;
	else
		divider = denominator;
	int aliquot1;
	int aliquot2;
	while (true)
	{
		aliquot1 = numerator_%divider;
		aliquot2 = denominator_%divider;
		if ((aliquot1 == 0)&&(aliquot2 == 0))
		{
			numerator = numerator/divider;
			denominator = denominator/divider;
			break;
		}
		divider--;
	}
	return *this;
}

Fraction Fraction::operator = (Fraction shot) 
{
	numerator = shot.getNumerator();
	denominator = shot.getDenominator();
	return *this;
}

Fraction Fraction::operator = (int number)
{
	numerator = number;
	denominator = 1;
	return *this;
}

bool Fraction::operator == (Fraction& shot)
{
	if ((numerator == shot.getNumerator())&&(denominator == shot.getDenominator()))
		return true;
	return false;
}

bool Fraction::operator == (int number)
{
	if ((numerator == number)&&(denominator == 1))
		return true;
	return false;
}

bool Fraction::operator != (Fraction& shot)
{
	if (*this == shot)
		return false;
	return true;
}

bool Fraction::operator != (int number)
{
	if (*this == number)
		return false;
	return true;
}

Fraction Fraction::operator + (Fraction& shot) const
{
	Fraction result;
	result.numerator = numerator*shot.getDenominator() + denominator*shot.getNumerator();
	result.denominator = denominator*shot.getDenominator();
	result.balancing();
	return result;
}

Fraction Fraction::operator + (int number) const
{
	Fraction result;
	result.numerator += number*denominator;
	result.balancing();
	return result;
}

Fraction Fraction::operator - (Fraction& shot) const
{
	Fraction result;
	result.numerator = numerator*shot.getDenominator() - denominator*shot.getNumerator();
	result.denominator = denominator*shot.getDenominator();
	result.balancing();
	return result;
}

Fraction Fraction::operator - (int number) const
{
	Fraction result;
	result.numerator = numerator - number*denominator;
	result.balancing();
	return result;
}

Fraction Fraction::operator * (Fraction& shot) const
{
	Fraction result;
	result.numerator = numerator*shot.getNumerator();
	result.denominator = denominator*shot.getDenominator();
	result.balancing();
	return result;
}

Fraction Fraction::operator * (int number) const
{
	Fraction result;
	result.numerator = numerator*number;
	result.balancing();
	return result;
}

Fraction Fraction::operator / (Fraction& shot) const
{
	Fraction result;
	result.numerator = numerator*shot.getDenominator();
	result.denominator = denominator*shot.getNumerator();
	result.balancing();
	return result;
}

Fraction Fraction::operator / (int number) const
{
	Fraction result;
	result.denominator = denominator*number;
	result.balancing();
	return result;
}

bool Fraction::operator < (Fraction& shot)
{
	*this = *this - shot;
	if ((this->numerator > 0)&&(this->denominator > 0))
		return false;
	if ((this->numerator < 0)&&(this->denominator < 0))
		return false;
	return true;
}

bool Fraction::operator < (int number)
{
	Fraction med(number);
	return *this < med;
}

bool Fraction::operator > (Fraction& shot)
{
	return shot < *this;
}

bool Fraction::operator > (int number)
{
	Fraction med(number);
	return med < *this;
}

bool Fraction::operator <= (Fraction& shot)
{
	if ((*this < shot)||(*this == shot))
		return true;
	return false;
}

bool Fraction::operator <= (int number)
{
	if ((*this < number)||(*this == number))
		return true;
	return false;
}

bool Fraction::operator >= (Fraction& shot)
{
	return shot <= *this;
}

bool Fraction::operator >= (int number)
{
	Fraction med(number);
	return med <= *this;
}

bool Fraction::isInt() const
{
	if (denominator == 1)
		return true;
	return false;
}

//==========================================ÊËÀÑÑ ÏÎËÈÍÎÌÛ=====================================================

class Polynomial
{
public:
	vector<Fraction> polynom;
	Fraction& operator[] (int i)
	{
		return polynom[i];
	}
	const Fraction& operator[] (int i) const
	{
		return polynom[i];
	}
	int degree() const
	{
		return polynom.size() - 1;
	}
	void setDegree(int degree)
	{
		polynom.resize(degree + 1);
	}
	Polynomial() 
	{
		polynom.assign(1, 0);
	}
	Polynomial (Polynomial& pol)
	{
		polynom.assign(pol.degree()+1, 0);
		for (int i = 0; i <= pol.degree(); i++)
		{
			polynom[i] = pol[i];
		}
	}
	Polynomial (int degree)
	{
		polynom.assign(degree+1, 0);
	}
	Polynomial operator = (Polynomial& pol);
	bool operator == (Polynomial& pol);
	bool operator == (int number);
	bool operator != (Polynomial& pol);
	bool operator != (int number);
	bool operator < (Polynomial& pol);
	bool operator <= (Polynomial& pol);
	bool operator > (Polynomial& pol);
	bool operator >= (Polynomial& pol);
	Polynomial operator - (Polynomial& pol);
	Polynomial operator + (Polynomial& pol);
	Polynomial operator * (Fraction& shot);
	Polynomial operator * (Polynomial& pol);
	Polynomial operator % (Polynomial& pol);
	void PrintPolynomial() const;
};

Polynomial Polynomial::operator = (Polynomial& pol)
{
	polynom.assign(pol.degree()+1, 0);
	for (int i = 0; i <= pol.degree(); i++)
	{
		polynom[i] = pol[i];
	}
	return *this;
}

bool Polynomial::operator == (Polynomial& pol)
{
	if (this->degree() == pol.degree())
	{
		for (int i = 0; i < pol.degree() + 1; i++)
		{
			if (polynom[i] != pol[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Polynomial::operator == (int number)
{
	if (polynom[0] == number)
	{
		for (int i = 1; i < this->degree() + 1; i++)
		{
			if (polynom[i] != 0)
				return false;
		}
		return true;
	}
	return false;
}

bool Polynomial::operator != (Polynomial& pol)
{
	if (*this == pol)
		return false;
	return true;
}

bool Polynomial::operator != (int number)
{
	if (*this == number)
		return false;
	return true;
}

bool Polynomial::operator < (Polynomial& pol)
{
	if (this->degree() < pol.degree())
		return true;
	if (this->degree() > pol.degree())
		return false;
	if (this->degree() == pol.degree())
	{
		for (int i = polynom.size()-1; i >= 0; i--)
		{
			if (polynom[i] < pol[i])
				return true;
			if (polynom[i] > pol[i])
				return false;
		}
		return true;
	}
}

bool Polynomial::operator <= (Polynomial& pol)
{
	if ((*this < pol)||(*this == pol))
		return true;
	return false;
}

bool Polynomial::operator > (Polynomial& pol)
{
	return (pol < *this);
}

bool Polynomial::operator >= (Polynomial& pol)
{
	return (pol <= *this);
}

Polynomial Polynomial::operator - (Polynomial& pol)
{
	Polynomial result;
	if (degree() < pol.degree())
	{
		result.setDegree(pol.degree());
		for (int i = 0; i < degree(); i++)
		{
			result.polynom[i] = polynom[i] - pol[i];
		}
		for (int i = degree(); i < pol.degree(); i++)
		{
			result.polynom[i] = Fraction() - pol[i];
		}
	}
	else
	{
		result.setDegree(degree());
		for (int i = 0; i < pol.degree(); i++)
		{
			result.polynom[i] = polynom[i] - pol[i];
		}
		for (int i = pol.degree(); i < degree(); i++)
		{
			result.polynom[i] = Fraction() - pol[i];
		}
	}
	return result;
}

Polynomial Polynomial::operator + (Polynomial& pol)
{
	Polynomial result;
	if (degree() < pol.degree())
	{
		result.setDegree(pol.degree());
		for (int i = 0; i < degree(); i++)
		{
			result.polynom[i] = polynom[i] + pol[i];
		}
		for (int i = degree(); i < pol.degree(); i++)
		{
			result.polynom[i] = pol[i];
		}
	}
	else
	{
		result.setDegree(degree());
		for (int i = 0; i < pol.degree(); i++)
		{
			result.polynom[i] = polynom[i] + pol[i];
		}
		for (int i = pol.degree(); i < degree(); i++)
		{
			result.polynom[i] = pol[i];
		}
	}
	return result;
}

Polynomial Polynomial::operator * (Fraction& shot)
{
	for (int i = 0; i < polynom.size(); i++)
		polynom[i] = polynom[i]*shot; 
	return *this;
}

Polynomial Polynomial::operator * (Polynomial& pol)
{
	Polynomial result(pol.degree() + degree());
	for (int i = 0; i < degree() + 1; i++)
	{
		for (int j = 0; j < pol.degree() + 1; j++)
		{
			Fraction med = pol[j]*polynom[i];
			result[i+j] = result[i+j] + med;
		}
	}
	int k = 1;
	while (result[result.polynom.size() - k] == 0)
	{
		result.setDegree(result.degree() - 1);
		k++;
	}
	return result;
}

Polynomial Polynomial::operator % (Polynomial& pol)
{
	Polynomial result = *this;
	if (degree() < pol.degree())
		return *this;
	Polynomial med(result.degree() - pol.degree());
	while (result.degree() >= pol.degree())
	{
		Fraction rate = Fraction(1) / pol[pol.degree()] * result[result.degree()];
		Polynomial rateX (result.degree() - pol.degree());
		rateX.polynom[rateX.degree()] = rate;
		Polynomial current = pol * rateX;
		result = result - current;
		result.setDegree(result.degree() - 1);
	}
	return result;
}

void Polynomial::PrintPolynomial() const
{
	if (polynom[0].isInt())
		if (polynom[0].getNumerator() != 0)
			cout << polynom[0].getNumerator() << " + ";
	else
		if (polynom[0].getNumerator() != 0)
			cout << polynom[0].getNumerator() << "/" << polynom[0].getDenominator() << " + ";
	for (int i = 1; i < polynom.size()-1; i++)
	{
		if (polynom[i].isInt())
			if (polynom[i].getNumerator() != 0)
				cout << polynom[i].getNumerator() << "x^" << i << " + ";
		else
			if (polynom[i].getNumerator() != 0)
				cout << polynom[i].getNumerator() << "/" << polynom[i].getDenominator() << "x^" << i << " + ";
	}
	if (polynom[polynom.size()-1].isInt())
		cout << polynom[polynom.size()-1].getNumerator() << "x^" << polynom.size()-1 << endl;
	else
		cout << polynom[polynom.size()-1].getNumerator() << "/" << polynom[0].getDenominator() << "x^" << polynom.size()-1 << endl;
}

template <class A>
A gcd (A a, A b)
{
	A first = a;
	A second = b;
	A med;
	while (second != 0)
	{
		med = second;
		second = first%second;
		first = med;
	}
	return first;
}

void GCD_test()
{
//=======Ïîëèíîìû=======

	Fraction a(1);
	Fraction b(2);

	Polynomial first1(1);
	Polynomial second1(2);
	first1.polynom[0] = a;
	first1.polynom[1] = a;
	second1.polynom[0] = a;
	second1.polynom[1] = b;
	second1.polynom[2] = a;
	Polynomial answer1 = gcd<Polynomial>(first1, second1);
	answer1.PrintPolynomial();

	Fraction c(3);
	Fraction d;
	Polynomial first2(2);
	Polynomial second2(2);
	first2.polynom[0] = c;
	first2.polynom[1] = d;
	first2.polynom[2] = c;
	second2.polynom[0] = a;
	second2.polynom[1] = d;
	second2.polynom[2] = a;
	Polynomial answer2 = gcd<Polynomial>(first2, second2);
	answer2.PrintPolynomial();

	Fraction f(9);
	Polynomial first3(1);
	Polynomial second3(3);
	first3.polynom[0] = a;
	first3.polynom[1] = a;
	second3.polynom[0] = c;
	second3.polynom[1] = f;
	second3.polynom[2] = f;
	second3.polynom[3] = c;
	Polynomial answer3 = gcd<Polynomial>(second3, first3);
	answer3.PrintPolynomial();

	Fraction i(4);
	Fraction j(5);
	Fraction k(6);
	Polynomial first4(2);
	Polynomial second4(3);
	first4.polynom[0] = k;
	first4.polynom[1] = j;
	first4.polynom[2] = a;
	second4.polynom[0] = b;
	second4.polynom[1] = j;
	second4.polynom[2] = i;
	second4.polynom[3] = a;
	Polynomial answer4 = gcd<Polynomial>(second4, first4);
	answer4.PrintPolynomial();

//=======×èñëà=======

	cout << gcd<int>(6, 15) << endl;
	cout << gcd<int>(5, 31) << endl;
	cout << gcd<int>(173, 91) << endl;
}

int main()
{
	GCD_test();
	//system("pause");
	return 0;
}