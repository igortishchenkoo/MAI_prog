#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

const int ROWS = 3;
const int COLS = 4;

double sinByN(double x, int n);
double sinByDelta(double x, double delta, int& termsCount);

void multiplyMatrixVector(double A[ROWS][COLS], double x[COLS], double y[ROWS]);
void printMatrix(double A[ROWS][COLS]);
void printVector(double v[], int size);

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color F0");

    cout << "Лабораторная работа №7" << endl;
    cout << "Пользовательские функции в языке C++" << endl;
    cout << "Вариант 25 -> вариант 1" << endl << endl;

    double xValue;
    int n;
    double delta;

    cout << "Часть 1. Вычисление sin(x) через ряд" << endl << endl;

    cout << "Введите x в радианах: ";
    cin >> xValue;

    cout << "Введите количество членов ряда n: ";
    cin >> n;

    cout << "Введите точность delta, например 0.000001: ";
    cin >> delta;

    if (n <= 0)
    {
        cout << "Ошибка: n должно быть положительным." << endl;
        system("pause");
        return 1;
    }

    if (delta <= 0)
    {
        cout << "Ошибка: delta должна быть положительной." << endl;
        system("pause");
        return 1;
    }

    double resultN;
    double resultDelta;
    double libraryResult;
    int termsCount;

    resultN = sinByN(xValue, n);
    resultDelta = sinByDelta(xValue, delta, termsCount);
    libraryResult = sin(xValue);

    cout << endl;
    cout << fixed << setprecision(10);

    cout << "Результаты вычислений:" << endl;
    cout << "sin(x) по " << n << " членам ряда = " << resultN << endl;
    cout << "sin(x) до точности delta = " << resultDelta << endl;
    cout << "Количество использованных членов ряда = " << termsCount << endl;
    cout << "sin(x) из библиотеки C++ = " << libraryResult << endl;

    cout << endl;
    cout << "Погрешность при вычислении по n членам:" << endl;
    cout << "|resultN - sin(x)| = " << fabs(resultN - libraryResult) << endl;

    cout << endl;
    cout << "Погрешность при вычислении до delta:" << endl;
    cout << "|resultDelta - sin(x)| = " << fabs(resultDelta - libraryResult) << endl;

    double A[ROWS][COLS] =
    {
        { 1.0,  2.0,  3.0,  4.0 },
        { 2.0,  0.0,  1.0, -1.0 },
        { 3.0,  1.0, -2.0,  2.0 }
    };

    double vectorX[COLS] = { 1.0, 2.0, 3.0, 4.0 };
    double vectorY[ROWS];

    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "Часть 2. Умножение матрицы на вектор-столбец" << endl << endl;

    cout << "Матрица A:" << endl;
    printMatrix(A);

    cout << endl;
    cout << "Вектор x:" << endl;
    printVector(vectorX, COLS);

    multiplyMatrixVector(A, vectorX, vectorY);

    cout << endl;
    cout << "Результат y = A * x:" << endl;
    printVector(vectorY, ROWS);

    cout << endl;
    cout << "Проверка вручную:" << endl;
    cout << "y[0] = 1*1 + 2*2 + 3*3 + 4*4 = 30" << endl;
    cout << "y[1] = 2*1 + 0*2 + 1*3 + (-1)*4 = 1" << endl;
    cout << "y[2] = 3*1 + 1*2 + (-2)*3 + 2*4 = 7" << endl;

    cout << endl;
    cout << "Вывод: в программе были созданы пользовательские функции ";
    cout << "для вычисления суммы ряда и для выполнения матрично-векторной операции." << endl;

    system("pause");
    return 0;
}

double sinByN(double x, int n)
{
    double sum = 0.0;
    double term = x;

    for (int i = 1; i <= n; i++)
    {
        sum = sum + term;

        term = -term * x * x / ((2.0 * i) * (2.0 * i + 1.0));
    }

    return sum;
}

double sinByDelta(double x, double delta, int& termsCount)
{
    double sum = 0.0;
    double term = x;
    int i = 1;

    termsCount = 0;

    do
    {
        sum = sum + term;
        termsCount++;
        term = -term * x * x / ((2.0 * i) * (2.0 * i + 1.0));
        i++;
    } while (fabs(term) >= delta);

    return sum;
}

void multiplyMatrixVector(double A[ROWS][COLS], double x[COLS], double y[ROWS])
{
    for (int i = 0; i < ROWS; i++)
    {
        y[i] = 0.0;

        for (int j = 0; j < COLS; j++)
        {
            y[i] = y[i] + A[i][j] * x[j];
        }
    }
}

void printMatrix(double A[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << setw(10) << fixed << setprecision(2) << A[i][j];
        }

        cout << endl;
    }
}

void printVector(double v[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << setw(10) << fixed << setprecision(2) << v[i] << endl;
    }
}