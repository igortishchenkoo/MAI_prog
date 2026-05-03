#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

struct FIO
{
    string surname;
    string name;
    string patronymic;
};

struct Pensioner
{
    FIO fio;
    char gender;
    int age;
    double pension;
};

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color F0");

    cout << "Лабораторная работа №6" << endl;
    cout << "Структуры в языке C++" << endl;
    cout << "Вариант 25 -> вариант 10" << endl;
    cout << "Структура «Пенсионер»: ФИО, пол, возраст, пенсия" << endl << endl;

    const int N = 3;

    Pensioner people[N];

    for (int i = 0; i < N; i++)
    {
        cout << "Введите данные пенсионера номер " << i + 1 << endl;

        cout << "Фамилия: ";
        cin >> people[i].fio.surname;

        cout << "Имя: ";
        cin >> people[i].fio.name;

        cout << "Отчество: ";
        cin >> people[i].fio.patronymic;

        cout << "Пол, М или Ж: ";
        cin >> people[i].gender;

        cout << "Возраст: ";
        cin >> people[i].age;

        cout << "Пенсия: ";
        cin >> people[i].pension;

        cout << endl;
    }

    cout << "Список пенсионеров:" << endl << endl;

    cout << left
        << setw(5) << "№"
        << setw(15) << "Фамилия"
        << setw(15) << "Имя"
        << setw(15) << "Отчество"
        << setw(8) << "Пол"
        << setw(10) << "Возраст"
        << setw(12) << "Пенсия"
        << endl;

    cout << string(80, '-') << endl;

    for (int i = 0; i < N; i++)
    {
        cout << left
            << setw(5) << i + 1
            << setw(15) << people[i].fio.surname
            << setw(15) << people[i].fio.name
            << setw(15) << people[i].fio.patronymic
            << setw(8) << people[i].gender
            << setw(10) << people[i].age
            << setw(12) << fixed << setprecision(2) << people[i].pension
            << endl;
    }

    double sumPension = 0.0;
    int maxIndex = 0;

    for (int i = 0; i < N; i++)
    {
        sumPension = sumPension + people[i].pension;

        if (people[i].pension > people[maxIndex].pension)
        {
            maxIndex = i;
        }
    }

    double averagePension = sumPension / N;

    cout << endl;
    cout << "Общая сумма пенсий: " << fixed << setprecision(2)
        << sumPension << endl;

    cout << "Средняя пенсия: " << fixed << setprecision(2)
        << averagePension << endl;

    cout << endl;
    cout << "Пенсионер с максимальной пенсией:" << endl;

    cout << people[maxIndex].fio.surname << " "
        << people[maxIndex].fio.name << " "
        << people[maxIndex].fio.patronymic << ", пенсия = "
        << fixed << setprecision(2)
        << people[maxIndex].pension << endl;

    cout << endl;
    cout << "Вывод: программа создала массив структур Pensioner, "
        << "считала данные, вывела их в виде таблицы и выполнила "
        << "обработку числового поля pension." << endl;

    system("pause");
    return 0;
}