#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    system("color F0");

    cout << "Лабораторная работа №8" << endl;
    cout << "Файловый ввод-вывод в C++. Текстовые файлы" << endl;
    cout << "Вариант 25" << endl << endl;

    string fileName = "poem.txt";

    ofstream outFile(fileName);

    if (!outFile)
    {
        cout << "Ошибка: не удалось открыть файл для записи." << endl;
        system("pause");
        return 1;
    }

    outFile << "Я помню чудное мгновенье:" << endl;
    outFile << "Передо мной явилась ты," << endl;
    outFile << "Как мимолетное виденье," << endl;
    outFile << "Как гений чистой красоты." << endl;

    outFile.close();

    cout << "Текст был записан в файл " << fileName << endl << endl;

    ifstream inFile(fileName);

    if (!inFile)
    {
        cout << "Ошибка: не удалось открыть файл для чтения." << endl;
        system("pause");
        return 2;
    }

    cout << "Содержимое файла:" << endl << endl;

    string line;

    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFile.close();

    cout << endl;
    cout << "Вывод: программа создала текстовый файл, записала в него строки," << endl;
    cout << "затем открыла этот файл для чтения и вывела его содержимое на консоль." << endl;

    system("pause");
    return 0;
}