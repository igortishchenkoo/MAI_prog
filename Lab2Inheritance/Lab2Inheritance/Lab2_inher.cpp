/*
 * Лабораторная работа №2. Вариант 7: точка - отрезок - треугольник - треугольная призма.
 * ВЕРСИЯ С НАСЛЕДОВАНИЕМ (чистовая, для отчёта).
 * Комментарии почти к каждой строке.
 */

#include <windows.h>
#include <math.h>
#include <iostream>
#include <cstdlib>

const double Pi = 3.14159265358979323846;

// Вспомогательная функция рисования отрезка
void DrawLine(HDC hdc, short x1, short y1, short x2, short y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

// Глобальный контекст устройства
HDC hdc = NULL;

// ------------------------------------------------------------------
// ИЕРАРХИЯ НАСЛЕДОВАНИЯ
// ------------------------------------------------------------------

// Базовый класс Точка
class Point {
protected:
    short X, Y;   // координаты точки на экране
    size_t C;     // цвет точки
public:
    // Конструктор с параметрами и умолчаниями
    Point(short x = 0, short y = 0, size_t c = RGB(0, 0, 0))
        : X(x), Y(y), C(c) {
    }

    // Акцессоры (геттеры) – возвращают значения защищённых полей
    short GetX() const { return X; }
    short GetY() const { return Y; }
    size_t GetC() const { return C; }

    // Акцессоры (сеттеры) – изменяют значения защищённых полей
    void PutX(short x) { X = x; }
    void PutY(short y) { Y = y; }
    void PutC(size_t c) { C = c; }

    // Метод рисования точки (будет унаследован потомками,
    // пока не переопределён – это демонстрирует проблему)
    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);   // создать перо цвета C
        SelectObject(hdc, pen);                 // выбрать перо в контекст
        // Рисуем утолщённую точку (маленький круг радиуса 2)
        short R = 2, Ri;
        for (char i = -1; i < 2; ++i) {
            Ri = R * i;
            Arc(hdc, X - Ri, Y - Ri, X + Ri, Y + Ri, X, Y + Ri, X, Y + Ri);
        }
        DeleteObject(pen);                      // удалить перо
    }

    // Метод стирания точки (рисует цветом фона)
    void Hide() {
        size_t oldC = C;                        // запоминаем цвет
        C = RGB(241, 241, 241);                 // меняем на цвет фона
        Show();                                 // рисуем (теперь цветом фона)
        C = oldC;                               // возвращаем цвет обратно
    }

    // Перемещение точки в новую позицию
    void MoveTo(short nx, short ny) {
        Hide();                                 // стереть старую
        PutX(nx);                               // задать новую X
        PutY(ny);                               // задать новую Y
        Show();                                 // нарисовать новую
    }
};

// Класс Отрезок, наследующий Point
class Line : public Point {
protected:
    short X2, Y2;   // координаты второго конца отрезка
    // координаты первого конца унаследованы (X, Y)
public:
    // Конструктор вызывает конструктор базового класса Point
    Line(short x1, short y1, short x2, short y2, size_t c)
        : Point(x1, y1, c), X2(x2), Y2(y2) {
    }

    // Акцессоры для полей, специфичных для отрезка
    short GetX2() const { return X2; }
    short GetY2() const { return Y2; }
    void PutX2(short x) { X2 = x; }
    void PutY2(short y) { Y2 = y; }

    // Собственный метод рисования отрезка (аналог Draw из методички)
    void Draw() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);            // используем унаследованные X,Y
        DeleteObject(pen);
    }

    // Собственный метод стирания отрезка
    void Clean() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Draw();
        C = oldC;
    }

    // Перемещение всего отрезка на dx, dy
    void Move(short dx, short dy) {
        Clean();                                // стереть
        X += dx; Y += dy;                       // сместить первую точку
        X2 += dx; Y2 += dy;                     // сместить вторую точку
        Draw();                                 // нарисовать
    }

    // Длина отрезка (вычисляется по координатам)
    double Length() const {
        return sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
    }
};

// Класс Треугольник, наследующий Line
class Triangle : public Line {
protected:
    short X3, Y3;   // координаты третьей вершины
    // первые две вершины унаследованы (X,Y) и (X2,Y2)
public:
    Triangle(short x1, short y1, short x2, short y2,
        short x3, short y3, size_t c)
        : Line(x1, y1, x2, y2, c), X3(x3), Y3(y3) {
    }

    // Акцессоры для третьей вершины
    short GetX3() const { return X3; }
    short GetY3() const { return Y3; }
    void PutX3(short x) { X3 = x; }
    void PutY3(short y) { Y3 = y; }

    // Собственный метод рисования треугольника
    void DrawTri() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        // Рисуем три стороны, используя все три вершины
        DrawLine(hdc, X, Y, X2, Y2);           // сторона между 1-й и 2-й
        DrawLine(hdc, X2, Y2, X3, Y3);         // между 2-й и 3-й
        DrawLine(hdc, X3, Y3, X, Y);           // между 3-й и 1-й
        DeleteObject(pen);
    }

    // Стирание треугольника
    void CleanTri() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        DrawTri();
        C = oldC;
    }

    // Перемещение всего треугольника
    void MoveTri(short dx, short dy) {
        CleanTri();
        X += dx; Y += dy;                       // двигаем первую вершину
        X2 += dx; Y2 += dy;                     // вторую
        X3 += dx; Y3 += dy;                     // третью
        DrawTri();
    }

    // Периметр треугольника
    double Perimeter() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        return a + b + c;
    }

    // Площадь треугольника (формула Герона)
    double Area() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

// Класс Треугольная призма, наследующий Triangle
class TriangularPrism : public Triangle {
protected:
    short Height;   // высота призмы (смещение верхнего основания по Y)
public:
    TriangularPrism(short x1, short y1, short x2, short y2,
        short x3, short y3, short height, size_t c)
        : Triangle(x1, y1, x2, y2, x3, y3, c), Height(height) {
    }

    // Акцессор для высоты
    short GetHeight() const { return Height; }
    void PutHeight(short h) { Height = h; }

    // Рисование треугольной призмы
    void DrawPrism() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);

        // Нижнее основание (текущий треугольник)
        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);

        // Верхнее основание (смещено вверх по Y на Height)
        short X1t = X, Y1t = Y - Height;
        short X2t = X2, Y2t = Y2 - Height;
        short X3t = X3, Y3t = Y3 - Height;
        DrawLine(hdc, X1t, Y1t, X2t, Y2t);
        DrawLine(hdc, X2t, Y2t, X3t, Y3t);
        DrawLine(hdc, X3t, Y3t, X1t, Y1t);

        // Боковые рёбра
        DrawLine(hdc, X, Y, X1t, Y1t);
        DrawLine(hdc, X2, Y2, X2t, Y2t);
        DrawLine(hdc, X3, Y3, X3t, Y3t);

        DeleteObject(pen);
    }

    // Стирание призмы
    void CleanPrism() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        DrawPrism();
        C = oldC;
    }

    // Перемещение призмы
    void MovePrism(short dx, short dy) {
        CleanPrism();
        // Двигаем только нижнее основание, верхнее пересчитается автоматически
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;
        DrawPrism();
    }

    // Объём призмы = площадь основания * высота
    double Volume() const {
        return Area() * Height;   // Area() унаследован от Triangle
    }
};

// ------------------------------------------------------------------
// ОСНОВНАЯ ПРОГРАММА
// ------------------------------------------------------------------
int main() {
    system("color f0");                     // белый фон консоли
    SetConsoleOutputCP(1251);               // русский язык в консоли
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();        // получаем графическое окно консоли
    hdc = GetWindowDC(hwnd);               // контекст устройства для рисования

    std::cout << "Лаб.раб.№2. Наследование. Вариант 7\n";

    // Создаём объекты с иерархией (X сдвинут на 350 вправо, чтобы не перекрыть текст)
    Point pt(200 + 350, 400, RGB(255, 0, 0));                        // красная точка
    Line ln(200 + 350, 350, 350 + 350, 400, RGB(0, 0, 255));         // синий отрезок
    Triangle tr(400 + 350, 300, 500 + 350, 400,
        450 + 350, 500, RGB(0, 128, 0));                     // зелёный треугольник
    TriangularPrism trpr(550 + 350, 350, 650 + 350, 380,
        600 + 350, 450, 70, RGB(255, 0, 255));      // фиолетовая призма

    // Демонстрация проблемы: унаследованные Show() рисуют только точку
    std::cout << "1. Унаследованный Show() работает неправильно:\n";
    pt.Show();   getchar();   // точка – ок
    ln.Show();   getchar();   // ожидается отрезок, рисуется точка (проблема)
    tr.Show();   getchar();   // ожидается треугольник, рисуется точка
    trpr.Show(); getchar();   // ожидается призма, рисуется точка

    // Показываем правильные собственные методы рисования
    std::cout << "2. Собственные методы рисования:\n";
    ln.Draw();   getchar();   // отрезок рисуется правильно
    tr.DrawTri(); getchar();  // треугольник правильно
    trpr.DrawPrism(); getchar(); // призма правильно

    // Движение объектов через собственные методы
    std::cout << "3. Движение объектов:\n";
    ln.Move(30, 10);          getchar();
    tr.MoveTri(-30, 20);      getchar();
    trpr.MovePrism(50, -10);  getchar();

    // Вычисляем геометрические параметры
    std::cout << "\nГеометрические параметры:\n";
    std::cout << "Длина отрезка: " << ln.Length() << std::endl;
    std::cout << "Периметр треугольника: " << tr.Perimeter() << std::endl;
    std::cout << "Площадь треугольника: " << tr.Area() << std::endl;
    std::cout << "Объём призмы: " << trpr.Volume() << std::endl;

    std::cout << "\nНажмите любую клавишу для завершения...";
    getchar();
    CloseWindow(hwnd);
    return 0;
}