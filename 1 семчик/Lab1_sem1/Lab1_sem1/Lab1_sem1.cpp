#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color F0");

    cout << "Лабораторная работа №1" << endl;
    cout << "Базовые типы данных в C++. Форматный и бесформатный ввод/вывод" << endl;
    cout << "Вариант 25" << endl << endl;

    // Часть 1: строки (ФИО и группа)
    string surname, name, patronymic, group;
    cout << "Часть 1. Строковые переменные" << endl;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите отчество: ";
    cin >> patronymic;
    cout << "Введите номер группы: ";
    cin >> group;

    // Формирование единой строки fiogr
    string fiogr = surname + " " + name + " " + patronymic + ", " + group;

    cout << "\nВывод через cout:" << endl;
    cout << "ФИО и группа: " << fiogr << endl;

    printf("\nВывод через printf:\n");
    printf("ФИО и группа: %s\n", fiogr.c_str());

    // Часть 2: целые типы
    cout << "\n----------------------------------------" << endl;
    cout << "Часть 2. Целые типы данных" << endl;

    // Знаковые типы
    char c = 100;                // день рождения (пример)
    short s = 2000;              // год рождения
    int i = 123456;              // почтовый индекс
    long l = 1234567890L;        // телефон (пример)
    long long ll = 8000000000LL; // население планеты (пример)

    // Беззнаковые типы
    unsigned char uc = 200;
    unsigned short us = 60000;
    unsigned int ui = 4000000000U;
    unsigned long ul = 4000000000UL;
    unsigned long long ull = 18000000000000000000ULL;

    cout << "Знаковые типы:" << endl;
    cout << "char c = " << (int)c << " (int day)" << endl;
    cout << "short s = " << s << " (year)" << endl;
    cout << "int i = " << i << " (index)" << endl;
    cout << "long l = " << l << " (phone)" << endl;
    cout << "long long ll = " << ll << " (population)" << endl;

    cout << "\nБеззнаковые типы:" << endl;
    cout << "unsigned char uc = " << (int)uc << endl;
    cout << "unsigned short us = " << us << endl;
    cout << "unsigned int ui = " << ui << endl;
    cout << "unsigned long ul = " << ul << endl;
    cout << "unsigned long long ull = " << ull << endl;

    // Ввод через scanf_s (пример для char и int)
    char c_in;
    int i_in;
    cout << "\nВведите символ и целое число через scanf_s:" << endl;
    scanf_s("%c %d", &c_in, 1, &i_in);
    printf("Вы ввели: символ '%c' (код %d), число %d\n", c_in, c_in, i_in);

    // Часть 3: исследование границ диапазонов
    cout << "\n----------------------------------------" << endl;
    cout << "Часть 3. Границы диапазонов целых типов" << endl;

    char c_max = 127;
    char c_overflow = c_max + 1; // переполнение
    cout << "char max + 1 = " << (int)c_overflow << " (должно быть -128)" << endl;

    unsigned char uc_max = 255;
    unsigned char uc_overflow = uc_max + 1;
    cout << "unsigned char max + 1 = " << (int)uc_overflow << " (должно быть 0)" << endl;

    // Размеры типов
    cout << "\nРазмеры типов в байтах:" << endl;
    cout << "char: " << sizeof(char) << endl;
    cout << "short: " << sizeof(short) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "long: " << sizeof(long) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    cout << "float: " << sizeof(float) << endl;
    cout << "double: " << sizeof(double) << endl;

    // Часть 4: вещественные типы
    cout << "\n----------------------------------------" << endl;
    cout << "Часть 4. Вещественные типы данных" << endl;

    float f_num = 0.123456789f;
    double d_num = 0.1234567890123456789;

    cout << "float (авто): " << f_num << endl;
    cout << "double (авто): " << d_num << endl;

    printf("printf float (e): %e\n", f_num);
    printf("printf double (e): %e\n", d_num);
    printf("printf float (f): %.10f\n", f_num);
    printf("printf double (f): %.15f\n", d_num);

    // Ввод вещественного числа через scanf_s
    double d_in;
    cout << "\nВведите вещественное число через scanf_s: ";
    scanf_s("%lf", &d_in);
    printf("Введено: %.15f\n", d_in);

    cout << "\n----------------------------------------" << endl;
    cout << "Вывод: в программе продемонстрированы базовые типы данных," << endl;
    cout << "форматный и бесформатный ввод/вывод, исследованы границы диапазонов." << endl;

    system("pause");
    return 0;
}