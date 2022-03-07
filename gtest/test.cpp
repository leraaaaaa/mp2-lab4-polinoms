#include "pch.h"
#include "../polynoms/polynoms.cpp"

TEST(Monomial, can_create_a_monom) {
	ASSERT_NO_THROW(Monomial* a=new Monomial);
}

TEST(Monomial, can_set_a_coeff_and_a_degree) {
	Monomial a;
	ASSERT_NO_THROW(a.coef=3.5);
	ASSERT_NO_THROW(a.degree = 387);
}

TEST(Polynomial, can_create_a_polynom) {
	ASSERT_NO_THROW(Polynomial a);
}

TEST(Polynomial, can_copy_a_polynom) {
	Polynomial a, b;
	a.ins(2, 234);
	a = a;
	b = a;
	a = b;
	ASSERT_NO_THROW(b=a);
}

TEST(Polynomial, equal_is_right) {
	Polynomial a, b;
	a.ins(3, 321);
	b.ins(3, 321);
	EXPECT_EQ(true, b == a);
}

TEST(Polynomial, copied_polynom_is_equal_to_first) {
	Polynomial a,b;
	a.ins(3, 321);
	b = a;
	EXPECT_EQ(true, b == a);
} 

TEST(Polynomial, can_insert) {
	Polynomial a;
	a.ins(7, 975);
	ASSERT_NO_THROW(a.ins(3, 321));
	ASSERT_NO_THROW(a.ins(5, 323));
}

TEST(Polynomial, can_delete) {
	Polynomial a;
	a.ins(3, 321);
	ASSERT_NO_THROW(a.del(3,321));
}

TEST(Polynomial, find_is_right1) {
	Polynomial a;
	Monomial* p=new Monomial;
	p->coef = 4;
	p->degree = 145;
	a.ins(3, 321);
	a.ins(4, 145);	
	a.ins(5, 287);
	EXPECT_EQ(true, a.find(p));
}

TEST(Polynomial, find_is_right2) {
	Polynomial a;
	Monomial* p = new Monomial;
	p->coef = 5;
	p->degree = 145;
	a.ins(3, 321);
	a.ins(4, 145);
	a.ins(5, 287);
	EXPECT_EQ(false, a.find(p));
}

TEST(Polynomial, can_upgrade) {
	Polynomial a;
	a.ins(3, 321);
	a.ins(6, 321);
	a.ins(-2, 321);
	Monomial* p = new Monomial;
	p->coef = 7;
	p->degree = 321;
	ASSERT_NO_THROW(a.upgrade());
	EXPECT_EQ(true, a.find(p));
}

TEST(Polynomial, can_mult) {
	Polynomial a,b;
	a.ins(3, 111);
	a.ins(6, 000);
	b.ins(-0.5, 111);
	b.ins(1.0, 000);
	Monomial* p = new Monomial;
	p->coef = 6;
	p->degree = 000;
	Monomial* q = new Monomial;
	q->coef = -1.5;
	q->degree = 222;
	ASSERT_NO_THROW(a*b);
	Polynomial c = a * b;
	ASSERT_NO_THROW(c.find(p));
	EXPECT_EQ(true, c.find(p));
	EXPECT_EQ(true, c.find(q));
}

TEST(Polynomial, mult_is_right) {
	Polynomial a, b;
	a.ins(3, 321);
	a.ins(6, 763);
	b.ins(-2, 321);
	b.ins(10, 153);
	ASSERT_ANY_THROW(a * b);
}

TEST(Polynomial, can_sum) {
	Polynomial a,b,c;
	a.ins(3, 321);
	a.ins(6, 763);
	b.ins(-2, 321);
	b.ins(10, 153);
	ASSERT_NO_THROW(c=a+b);
}

TEST(Polynomial, sum_is_right) {
	Polynomial a, b;
	a.ins(3, 321);
	a.ins(6, 763);
	b.ins(-2, 321);
	b.ins(10, 153);
	Monomial* p = new Monomial;
	p->coef = 1;
	p->degree = 321;
	Monomial* q = new Monomial;
	q->coef = 6;
	q->degree = 763;
	Monomial* z = new Monomial;
	z->coef = 10;
	z->degree = 153;
	Polynomial c = a + b;
	EXPECT_EQ(true, c.find(z) && c.find(p) && c.find(q));
}

TEST(Polynomial, arithmetic_is_right) {
	Polynomial a,b;
	a.ins(3, 321);
	b.ins(4, 381);
	EXPECT_EQ(b,b+a-a);
}

TEST(Polynomial, sub_is_right) {
	Polynomial a, b;
	a.ins(3, 321);
	a.ins(6, 763);
	b.ins(-2, 321);
	b.ins(10, 153);
	Monomial* p = new Monomial;
	p->coef = 5;
	p->degree = 321;
	Monomial* q = new Monomial;
	q->coef = 6;
	q->degree = 763;
	Monomial* z = new Monomial;
	z->coef = -10;
	z->degree = 153;
	Polynomial c = a - b;
	EXPECT_EQ(true, c.find(p) && c.find(q) && c.find(z));
}
