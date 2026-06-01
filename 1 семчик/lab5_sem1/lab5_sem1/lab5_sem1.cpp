#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color F0");

    cout << "Лабораторная работа №5" << endl;
    cout << "Структурирование информации. Массивы и указатели" << endl;
    cout << "Вариант 25 -> задание 1" << endl << endl;

    const int N = 8;
    char symbols[N] = { '+', '-', '*', '/', '%', '=', '>', '<' };

    cout << "Часть 1. Одномерный массив символов" << endl << endl;

    cout << setw(12) << "Символы:";
    for (int i = 0; i < N; i++)
    {
        cout << setw(5) << symbols[i];
    }
    cout << endl;

    cout << setw(12) << "Номера:";
    for (int i = 0; i < N; i++)
    {
        cout << setw(5) << i + 1;
    }
    cout << endl;

    cout << setw(12) << "ASCII:";
    for (int i = 0; i < N; i++)
    {
        cout << setw(5) << (int)symbols[i];
    }
    cout << endl << endl;

    cout << "Пояснение: массив symbols хранит символы арифметических действий." << endl;
    cout << "Индекс массива в C++ начинается с 0, поэтому номер элемента равен i + 1." << endl;
    cout << "ASCII-код получаем приведением символа к типу int." << endl << endl;

    const int ROWS = 3;
    const int COLS = 4;

    double A[ROWS][COLS] =
    {
        { 1.0,  2.0,  3.0,  4.0 },
        { 2.0,  0.0,  1.0, -1.0 },
        { 3.0,  1.0, -2.0,  2.0 }
    };

    double x[COLS] = { 1.0, 2.0, 3.0, 4.0 };
    double y[ROWS];

    cout << "----------------------------------------" << endl;
    cout << "Часть 2. Умножение матрицы на вектор-столбец" << endl << endl;

    cout << "Матрица A:" << endl;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << setw(8) << fixed << setprecision(2) << A[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "Вектор-столбец x:" << endl;
    for (int j = 0; j < COLS; j++)
    {
        cout << setw(8) << fixed << setprecision(2) << x[j] << endl;
    }

    for (int i = 0; i < ROWS; i++)
    {
        y[i] = 0.0;

        for (int j = 0; j < COLS; j++)
        {
            y[i] = y[i] + A[i][j] * x[j];
        }
    }

    cout << endl;
    cout << "Результат y = A * x:" << endl;
    for (int i = 0; i < ROWS; i++)
    {
        cout << setw(8) << fixed << setprecision(2) << y[i] << endl;
    }

    cout << endl;
    cout << "Пояснение: каждый элемент вектора y получается как сумма произведений" << endl;
    cout << "элементов строки матрицы A на соответствующие элементы вектора x." << endl;

    cout << endl;
    cout << "Вывод: в работе были использованы одномерный массив символов," << endl;
    cout << "двумерный массив для хранения матрицы и одномерные массивы для" << endl;
    cout << "хранения входного и выходного векторов." << endl;

    system("pause");
    return 0;
}