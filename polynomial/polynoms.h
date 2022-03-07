#ifndef _POLYNOMS_H_
#define _POLYNOMS_H_
#include <iostream>
using namespace std;

struct Monomial
{
	Monomial* pNext;
	Monomial* pEarl;
	double coef;
	int degree;
};

class Polynomial
{
private:
	Monomial* head;
public:
	Monomial* getHead()
	{
		return head;
	}
	
	Polynomial();
	Polynomial(const Polynomial& A);
	~Polynomial();

	Polynomial operator+ (const Polynomial& A) const;
	Polynomial operator- (const Polynomial& A) const;
	Polynomial operator* (const Polynomial& A);
	Polynomial operator* (double a) const;
	bool operator==(const Polynomial& A) const;
	Polynomial& operator= (const Polynomial& A);	

	void cleanMonomial(Monomial* A);
	void cleanPolynomial();
	
	
	void ins(double c, int d);
	void del(double c, int d);
	bool degree_is_correct(int deg)
	{
		if (deg < 0 || deg > 999)
			return false;
		else return true;
	}
	void upgrade();
	int digit_sum(int A)
	{
		int s = 0;
		while (A > 0)
		{
			s = s + A % 10;
			A = A / 10;
		}
		return s;
	}
	bool find(Monomial* A);
	friend istream& operator >> (istream& in, Polynomial& A);
	friend ostream& operator << (ostream& out, const Polynomial& A);
};

#endif
