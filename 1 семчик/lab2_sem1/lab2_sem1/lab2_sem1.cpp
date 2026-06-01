#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("color F0");

	cout << "Лабораторная работа н. 2" << endl;
	cout << "Линейный вичслительный процесс" << endl;
	cout << "Вариант 25" << endl << endl;

	double a;
	double b;
	double h;
	double S;

	cout << "Часть 1. Площадь трапеции" << endl;
	cout << "Введите первое основание трапеции а: ";
	cin >> a;

	cout << "Введите второе основание трапеции b: ";
	cin >> b;

	cout << "Введите высоту трапеции h: ";
	cin >> h;

	S = (a + b) * h / 2.0;

	cout << endl;
	cout << "Результат через cout:" << endl;
	cout << fixed << setprecision(6);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "h = " << h << endl;
	cout << "S = (a + b) * h / 2 = " << S << endl;

	printf("\nРезультат через printf в пользовательском формате:\n");
	printf("a = %.3f\n", a);
	printf("b = %.3f\n", b);
	printf("h = %.3f\n", h);
	printf("S = %.3f\n", S);

    double x;
    double left;
    double right;
    double difference;
    double abs_difference;

    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "Часть 2. Проверка гиперболического тождества" << endl;
    cout << "th(x) * ch(x) / sh(x) = 1" << endl;
    cout << "В C++: tanh(x) * cosh(x) / sinh(x) = 1" << endl;
    cout << "Введите x, причём x не должен быть равен 0: ";
    cin >> x;

    left = tanh(x) * cosh(x) / sinh(x);
    right = 1.0;
    difference = left - right;
    abs_difference = fabs(difference);

    cout << endl;
    cout << "Результат проверки через cout:" << endl;
    cout << setprecision(15);
    cout << "x = " << x << endl;
    cout << "Левая часть = tanh(x) * cosh(x) / sinh(x) = " << left << endl;
    cout << "Правая часть = " << right << endl;
    cout << "Разность left - right = " << difference << endl;
    cout << "Модуль разности |left - right| = " << abs_difference << endl;

    printf("\nРезультат проверки через printf:\n");
    printf("x = %.10f\n", x);
    printf("left = %.15f\n", left);
    printf("right = %.15f\n", right);
    printf("left - right = %.15f\n", difference);
    printf("|left - right| = %.15f\n", abs_difference);

    cout << endl;
    cout << "Вывод: если модуль разности близок к нулю, ";
    cout << "то вычисления подтверждают истинность тождества." << endl;

    system("pause");
    return 0;
}