#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("color F0");

	cout << "Лабораторная работа н. 3" << endl;
	cout << "Ветвящиеся вычислительные процессы" << endl;
	cout << "Вариант 25" << endl << endl;

	double x;
	double y;

	cout << "Часть 1. Вычисление кусочно заданной функции" << endl;
	cout << "Введите x: ";
	cin >> x;

	if (x > 0)
	{
		y = log10(x);
		cout << "Так как x > 0, используем формулу y = lg(x)." << endl;
	}
	else if (x == 0)
	{
		y = 0;
		cout << "Так как х = 0, используем формулу y = 0." << endl;
	}
	else
	{
		y = pow(10.0, x);
		cout << "Так как х < 0, используем формулу y = 10^x" << endl;
	}

	cout << fixed << setprecision(6);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	int digit;

	cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "Часть 2. Оператор switch" << endl;
    cout << "Введите цифру от 0 до 9: ";
    cin >> digit;

    cout << "Название цифры: ";

    switch (digit)
    {
    case 0:
        cout << "ноль";
        break;

    case 1:
        cout << "один";
        break;

    case 2:
        cout << "два";
        break;

    case 3:
        cout << "три";
        break;

    case 4:
        cout << "четыре";
        break;

    case 5:
        cout << "пять";
        break;

    case 6:
        cout << "шесть";
        break;

    case 7:
        cout << "семь";
        break;

    case 8:
        cout << "восемь";
        break;

    case 9:
        cout << "девять";
        break;

    default:
        cout << "ошибка: введено не число от 0 до 9";
        break;
    }

    cout << endl << endl;

    cout << "Вывод: в программе были использованы оператор if-else ";
    cout << "для вычисления кусочно заданной функции и оператор switch ";
    cout << "для выбора значения по входной переменной." << endl;

    system("pause");
    return 0;
}