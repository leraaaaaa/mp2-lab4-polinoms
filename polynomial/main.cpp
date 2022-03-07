#include "polynoms.h"
using namespace std;
int main()
{
setlocale(LC_ALL, "Russian");
int choise;
cout << "Выберите желаемое действие:" << endl << "1. Сложение полиномов" << endl << "2. Вычитание полиномов" << endl << "3. Умножение полиномов" << endl << "4. Умножение полинома на скаляр" << endl;
cin >> choise;
switch (choise)
{
case 1:
{
	Polynomial a, b;
	try
	{
		cout << "Введите первое слагаемое:"<<endl;
		cin >> a;
		cout << endl << "Введите второе слагаемое:" << endl;
		cin >> b;
		cout << endl << a << " + " << b << " = " << a + b << endl;
	}
	catch(...)
	{
		cout << "Некорректный ввод полинома!" << endl;
	}
	break;
}
case 2:
{
	Polynomial a, b;
	try {
		cout << "Введите уменьшаемое:" << endl;
		cin >> a;
		cout << endl << "Введите вычитаемое:" << endl;
		cin >> b;
		cout << endl << a << " - " << b << " = " << a - b << endl;
	}
	catch (...)
	{
		cout << "Некорректный ввод полинома!" << endl;
	}
	break;
}
case 3:
{
	Polynomial a, b;
	try {
		cout << "Введите первый множитель:"<<endl;
		cin >> a;
		cout << endl << "Введите второй множитель:" << endl;
		cin >> b;
		
	}
	catch (...)
	{
	cout << "Некорректный ввод полинома!" << endl;
	}
	try
	{
		cout << endl << "(" << a << ") * (" << b << ")" << " = " << a * b << endl;
	}
	catch (...)
	{
		cout << "Некорректная степень произведения!" << endl;
	}
	break;
}
case 4:
{
	Polynomial a;
	double b;
	try
	{
		cout << "Введите полином:" << endl;
		cin >> a;
		cout << endl << "Введите скаляр:" << endl;
		cin >> b;
		cout << endl << a << " * " << b << " = " << a * b << endl;
	}
	catch (...)
	{
		cout << "Некорректный ввод полинома!" << endl;
	}
	break;
}
default:
{
	cout << "Недопустимая операция!";
	break;
}
}
return 0;
}
