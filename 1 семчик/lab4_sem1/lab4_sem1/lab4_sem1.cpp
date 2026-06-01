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

	cout << "Лабораторная работа н. 4" << endl;
	cout << "Циклические вычислительные процессы" << endl;
	cout << "Вариант 25 (10)" << endl << endl;

	int n;
	double eps;

	cout << "Введите кол-во членов ряда n: ";
	cin >> n;

	cout << "Введите точность eps, например 0.001: ";
	cin >> eps;

	if (n <= 0)
	{
		cout << "Ошибка: n должно быть положительным." << endl;
		return 1;
	}

	if (eps <= 0)
	{
		cout << "Ошибка: eps должно быть положительным." << endl;
		return 1;
	}

	cout << fixed << setprecision(10);

	double sum_for = 0.0;
	double pi_for;

	for (int i = 1; i <= n; i++)
	{
		sum_for = sum_for + 1.0 / ((double)i * i);
	}

	pi_for = sqrt(6.0 * sum_for);

	cout << endl;
	cout << "1) Вычисление через цикл for" << endl;
	cout << "Сумма = " << sum_for << endl;
	cout << "pi = " << pi_for << endl;

	double sum_while = 0.0;
	double pi_old = 0.0;
	double pi_new = 0.0;
	double difference = eps;
	int i = 1;

	while (difference >= eps)
	{
		pi_old = pi_new;

		sum_while = sum_while + 1.0 / ((double)i * i);
		pi_new = sqrt(6.0 * sum_while);

		difference = fabs(pi_new - pi_old);

		i++;
	}

	cout << endl;
	cout << "2) Вычисление через цикл while до точности eps" << endl;
	cout << "Количество использованных членов ряда = " << i - 1 << endl;
	cout << "Сумма = " << sum_while << endl;
	cout << "pi = " << pi_new << endl;
	cout << "|pi_new - pi_old| = " << difference << endl;

	double sum_do = 0.0;
	double pi_old_do = 0.0;
	double pi_new_do = 0.0;
	double difference_do;
	int j = 1;

	do
	{
		pi_old_do = pi_new_do;

		sum_do = sum_do + 1.0 / ((double)j * j);
		pi_new_do = sqrt(6.0 * sum_do);

		difference_do = fabs(pi_new_do - pi_old_do);

		j++;
	} while (difference_do >= eps);
	cout << endl;
	cout << "3) Вычисление через цикл do while до точности eps" << endl;
	cout << "Количество использованных членов ряда = " << j - 1 << endl;
	cout << "Сумма = " << sum_do << endl;
	cout << "pi = " << pi_new_do << endl;
	cout << "|pi_new - pi_old| = " << difference_do << endl;

	cout << endl;
	cout << "Настоящее значение pi из библиотеки C++:" << endl;
	cout << "acos(-1) = " << acos(-1.0) << endl;

	cout << endl;
	cout << "Вывод: в программе были использованы циклы for, while и do while. ";
	cout << "Цикл for применялся при заранее известном количестве повторений, ";
	cout << "а циклы while и do while применялись для вычисления до заданной точности." << endl;

	system("pause");
	return 0;
}