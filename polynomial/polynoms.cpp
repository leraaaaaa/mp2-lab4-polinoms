#include "polynoms.h"

Polynomial::Polynomial()
{
	Monomial* p = new Monomial;
	p->degree = -1;
	p->coef = 0.0;
	p->pEarl = nullptr;
	p->pNext = nullptr;
	head = p;
}
Polynomial::Polynomial(const Polynomial& A)
{
	Monomial* p = new Monomial;
	p->degree = -1;
	p->coef = 0.0;
	p->pEarl = nullptr;
	p->pNext = nullptr;
	head = p;
	p = A.head->pNext;
	while (p != nullptr)
	{
		ins(p->coef, p->degree);
		p = p->pNext;
	}
}
Polynomial::~Polynomial()
{
	Monomial* p = head;
	while (p->pNext != nullptr)
	{
		Monomial* q = p;
		p = p->pNext;
		delete q;
	}
	delete p;
}

Polynomial Polynomial::operator+ (const Polynomial& A) const
{
	Polynomial S;
	Monomial* s1 = A.head->pNext;
	Monomial* s2 = head->pNext;
	while (s1 != nullptr || s2 != nullptr)
	{
		if (s1 == nullptr)
		{
			while (s2 != nullptr)
			{
				S.ins(s2->coef, s2->degree);
				s2 = s2->pNext;
			}
			break;
		}
		while (s1 != nullptr && s2 != nullptr && ((s1->degree) > (s2->degree)))
		{
			S.ins(s1->coef, s1->degree);
			s1 = s1->pNext;
		}
		if (s2 == nullptr)
		{
			while (s1 != nullptr)
			{
				S.ins(s1->coef, s1->degree);
				s1 = s1->pNext;
			}
			break;
		}
		while (s2 != nullptr && s1 != nullptr && ((s2->degree) >= (s1->degree)))
		{
			S.ins(s2->coef, s2->degree);
			s2 = s2->pNext;
		}
	}
	S.upgrade();
	return S;
}

Polynomial Polynomial::operator- (const Polynomial& A) const
{
	return (*this + A * (-1.0));
}


Polynomial Polynomial::operator*(const Polynomial& p)
{
	Polynomial a;
	Monomial* k = head->pNext;
	while (k != nullptr) {
		Monomial* q = p.head->pNext;
		while (q != nullptr) {
			if (digit_sum(k->degree) + digit_sum(q->degree) != digit_sum(k->degree + q->degree)) throw "invalid degree";
			a.ins((k->coef * q->coef), (k->degree + q->degree));
			q = q->pNext;
		}
		k = k->pNext;
	}
	a.upgrade();
	return a;
}

Polynomial Polynomial::operator* (double a) const
{
	if (abs(a) < 1e-10)
	{
		Polynomial A;
		return A;
	}
	else
	{
		Polynomial A = *this;
		Monomial* p = A.head->pNext;
		while (p != nullptr)
		{
			p->coef = p->coef * a;
			p = p->pNext;
		}
		return A;
	}
}

bool Polynomial::operator==(const Polynomial& A) const
{
	Monomial* cmp1 = A.head->pNext;
	Monomial* cmp2 = head->pNext;
	while ((cmp1 != nullptr) && (cmp2 != nullptr))
	{
		if (abs(cmp1->coef - cmp2->coef) > 1e-10)
			return false;
		if (cmp1->degree != cmp2->degree)
			return false;
		cmp1 = cmp1->pNext;
		cmp2 = cmp2->pNext;
	}
	if ((cmp1 != nullptr) || (cmp2 != nullptr))
		return false;
	return true;
}

Polynomial& Polynomial::operator=(const Polynomial& A)
{
	if (head != A.head) {
		Monomial* temp = head->pNext;
		if (temp != NULL) {
			while (temp->pNext != NULL) {
				temp = temp->pNext;
				delete temp->pEarl;
			}
			delete temp;
		}
		head->pNext = NULL;
		Monomial* temp_h = A.head->pNext;
		while (temp_h != NULL) {
			ins(temp_h->coef, temp_h->degree);
			temp_h = temp_h->pNext;
		}
	}
	return *this;
}

void Polynomial::cleanMonomial(Monomial* A)
{
	if (find(A) == true)
	{
		Monomial* p = A;
		p = p->pNext;
		delete p->pEarl;
	}
}

void Polynomial::cleanPolynomial()
{
	Monomial* p = head;
	while (p->pNext != nullptr)
	{
		cleanMonomial(p->pNext);
		p = p->pNext;
	}
	delete p;
}

void Polynomial::ins(double c, int d)
{
	if (!degree_is_correct(d)) throw "invalid degree";
	if (abs(c) < 1e-10) throw "invalid coefficient";
	Monomial* p = head;
	while ((p->pNext != nullptr) && (p->pNext->degree>d))
		p = p->pNext;
	Monomial* q = new Monomial;
	q->coef = c;
	q->degree = d;
	if (p->pNext != nullptr)
	{
		q->pNext = p->pNext;
		q->pEarl = p;
		p->pNext->pEarl=q;
		p->pNext = q;
	}
	else
	{
		q->pNext = nullptr;
		q->pEarl = p;
		p->pNext = q;
	}
	upgrade();
}

void Polynomial::del(double c, int d)
{
	Monomial* p = head->pNext;
	while ((p != nullptr) && ((p->coef != c) || (p->degree != d)))
		p = p->pNext;
	if (p != nullptr)
	{
		if (p->pNext != nullptr) {
			p->pEarl->pNext = p->pNext;
			p->pNext->pEarl = p->pEarl;
		}
		else
		{
			p->pEarl->pNext = nullptr;
		}
		delete p;
	}
}

void Polynomial::upgrade()
{
	Monomial* p = head;
	while (p->pNext != nullptr)
	{
		if (abs(p->pNext->coef) < 1e-10)
		{
			del(p->pNext->coef, p->pNext->degree);
			continue;
		}
		if ((p->pNext->pNext != nullptr) && (p->pNext->degree == p->pNext->pNext->degree))
		{
			if (abs(p->pNext->pNext->coef + p->pNext->coef) < 1e-10)
			{
				del(p->pNext->pNext->coef, p->pNext->pNext->degree);
				del(p->pNext->coef, p->pNext->degree);
				continue;
			}
			else
			{
				p->pNext->coef = p->pNext->coef + p->pNext->pNext->coef;
				del(p->pNext->pNext->coef, p->pNext->pNext->degree);
				continue;
			}
		}
		p = p->pNext;
	}
	if (abs(p->coef) < 1e-10)
		del(p->coef, p->degree);
}

bool Polynomial::find(Monomial* A)
{
	Monomial* p = head->pNext;
	while (p != nullptr)
	{
		if ((p->coef == A->coef) && (p->degree == A->degree))
			return true;
		p = p->pNext;
	}
	return false;
}

istream& operator >> (istream& in, Polynomial& A)
{
	cout << "Введите количество мономов в полиноме: "<<endl;
	int n, d = 0;
	double c;
	cin >> n;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "Введите коэффициент " << i+1 << " монома: "<<endl;
		cin >> c;
		if (abs(c) < 1e-10)
			continue;
		cout << "Введите степени x,y,z " << i + 1 << " монома в виде трехзначного числа: "<<endl;
		cin >> d;
		if (d < 0 || d > 999) throw "invalid degree";
		A.ins(c, d);
	}
	return in;
}

ostream& operator << (ostream& out, const Polynomial& A)
{
	Monomial* p = A.head->pNext;
	if (p == nullptr)
	{
		cout << 0;
		return out;
	}
	while (p != nullptr)
	{
		cout << "(";
		cout << p->coef;
		if ((p->degree / 100) % 10 != 0)
			cout << "*x^" << (p->degree / 100) % 10;
		if ((p->degree / 10) % 10 != 0)
			cout << "*y^" << (p->degree / 10) % 10;
		if (p->degree % 10 != 0)
			cout << "*z^" << p->degree % 10;
		cout << ")";
		if (p->pNext != nullptr)
			cout << "+";
		p = p->pNext;
	}
	return out;
}
