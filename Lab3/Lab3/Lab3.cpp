/*
 * Лабораторная работа №3. Вариант 7: точка - отрезок - треугольник - треугольная призма.
 * Переопределение методов и перегрузка конструкторов.
 * Монолитный файл с комментариями.
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

// Глобальный контекст устройства (рисование)
HDC hdc = NULL;

// ------------------------------------------------------------------
// БАЗОВЫЙ КЛАСС: Точка
// ------------------------------------------------------------------
class Point {
protected:
    short X, Y;     // координаты
    size_t C;       // цвет
public:
    // --- Перегруженные конструкторы ---
    // 1) Конструктор с параметрами и значениями по умолчанию (полный набор)
    Point(short x = 0, short y = 0, size_t c = RGB(0, 0, 0))
        : X(x), Y(y), C(c) {
    }

    // 2) Конструктор по умолчанию (без параметров) – явно задаём нули
    // (в данном случае предыдущий конструктор с умолчаниями уже покрывает этот случай,
    //  но для наглядности перегрузки оставим оба варианта, можно объединить)
    // Point() : X(0), Y(0), C(RGB(0,0,0)) {}   // раскомментировать, если нужно строго два

    // Акцессоры
    short GetX() const { return X; }
    short GetY() const { return Y; }
    size_t GetC() const { return C; }
    void PutX(short x) { X = x; }
    void PutY(short y) { Y = y; }
    void PutC(size_t c) { C = c; }

    // Методы рисования (будут переопределяться в потомках)
    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        // Рисуем точку как маленький круг
        short R = 2, Ri;
        for (char i = -1; i < 2; ++i) {
            Ri = R * i;
            Arc(hdc, X - Ri, Y - Ri, X + Ri, Y + Ri, X, Y + Ri, X, Y + Ri);
        }
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);   // цвет фона
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        Hide();
        PutX(nx);
        PutY(ny);
        Show();
    }
};

// ------------------------------------------------------------------
// КЛАСС-НАСЛЕДНИК: Отрезок
// ------------------------------------------------------------------
class Line : public Point {
protected:
    short X2, Y2;   // координаты второго конца
public:
    // --- Перегруженные конструкторы ---
    // 1) Полный конструктор
    Line(short x1, short y1, short x2, short y2, size_t c)
        : Point(x1, y1, c), X2(x2), Y2(y2) {
    }

    // 2) Конструктор по умолчанию (вызывает Point по умолчанию)
    Line() : Point(), X2(0), Y2(0) {}

    // Акцессоры
    short GetX2() const { return X2; }
    short GetY2() const { return Y2; }
    void PutX2(short x) { X2 = x; }
    void PutY2(short y) { Y2 = y; }

    // Переопределённые методы (заменяют Draw, Clean, Move)
    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);   // используем унаследованные X,Y
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();                         // вызовет переопределённый Show
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        // Перемещаем оба конца так, чтобы первая точка оказалась в (nx,ny)
        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        Show();
    }

    // Длина остаётся
    double Length() const {
        return sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
    }
};

// ------------------------------------------------------------------
// КЛАСС-НАСЛЕДНИК: Треугольник
// ------------------------------------------------------------------
class Triangle : public Line {
protected:
    short X3, Y3;   // третья вершина
public:
    // --- Перегруженные конструкторы ---
    // 1) Полный
    Triangle(short x1, short y1, short x2, short y2,
        short x3, short y3, size_t c)
        : Line(x1, y1, x2, y2, c), X3(x3), Y3(y3) {
    }

    // 2) По умолчанию
    Triangle() : Line(), X3(0), Y3(0) {}

    // Акцессоры
    short GetX3() const { return X3; }
    short GetY3() const { return Y3; }
    void PutX3(short x) { X3 = x; }
    void PutY3(short y) { Y3 = y; }

    // Переопределённые методы
    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);
        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);
        DeleteObject(pen);
    }

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;
        Show();
    }

    double Perimeter() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        return a + b + c;
    }

    double Area() const {
        double a = sqrt(pow(X2 - X, 2.0) + pow(Y2 - Y, 2.0));
        double b = sqrt(pow(X3 - X2, 2.0) + pow(Y3 - Y2, 2.0));
        double c = sqrt(pow(X - X3, 2.0) + pow(Y - Y3, 2.0));
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

// ------------------------------------------------------------------
// КЛАСС-НАСЛЕДНИК: Треугольная призма
// ------------------------------------------------------------------
class TriangularPrism : public Triangle {
protected:
    short Height;   // высота призмы
public:
    // --- Перегруженные конструкторы ---
    // 1) Полный
    TriangularPrism(short x1, short y1, short x2, short y2,
        short x3, short y3, short height, size_t c)
        : Triangle(x1, y1, x2, y2, x3, y3, c), Height(height) {
    }

    // 2) По умолчанию
    TriangularPrism() : Triangle(), Height(0) {}

    // Акцессор
    short GetHeight() const { return Height; }
    void PutHeight(short h) { Height = h; }

    // Переопределённые методы
    void Show() {
        HPEN pen = CreatePen(PS_SOLID, 2, C);
        SelectObject(hdc, pen);

        // Нижнее основание (текущий треугольник)
        DrawLine(hdc, X, Y, X2, Y2);
        DrawLine(hdc, X2, Y2, X3, Y3);
        DrawLine(hdc, X3, Y3, X, Y);

        // Верхнее основание (смещено по Y на Height вверх)
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

    void Hide() {
        size_t oldC = C;
        C = RGB(241, 241, 241);
        Show();
        C = oldC;
    }

    void MoveTo(short nx, short ny) {
        short dx = nx - X;
        short dy = ny - Y;
        Hide();
        X += dx; Y += dy;
        X2 += dx; Y2 += dy;
        X3 += dx; Y3 += dy;
        // Height не меняется, верхнее основание автоматически пересчитается при Show()
        Show();
    }

    double Volume() const {
        return Area() * Height;   // площадь основания унаследована от Triangle
    }
};

// ------------------------------------------------------------------
// ОСНОВНАЯ ПРОГРАММА
// ------------------------------------------------------------------
int main() {
    system("color f0");                     // светлый фон консоли
    SetConsoleOutputCP(1251);               // поддержка кириллицы
    SetConsoleCP(1251);

    HWND hwnd = GetConsoleWindow();
    hdc = GetWindowDC(hwnd);

    std::cout << "Лабораторная работа №3. Переопределение и перегрузка.\n";
    std::cout << "Вариант 7: точка - отрезок - треугольник - треугольная призма.\n\n";

    // ---------- Часть 1: Демонстрация переопределённых методов ----------
    std::cout << "1. Рисование с помощью единого имени Show():\n";

    // Создаём объекты с полными конструкторами (сдвинуты вправо на 350)
    Point pt(200 + 350, 400, RGB(255, 0, 0));                     // красная точка
    Line ln(200 + 350, 350, 350 + 350, 400, RGB(0, 0, 255));      // синий отрезок
    Triangle tr(400 + 350, 300, 500 + 350, 400,
        450 + 350, 500, RGB(0, 128, 0));                  // зелёный треугольник
    TriangularPrism pr(550 + 350, 350, 650 + 350, 380,
        600 + 350, 450, 70, RGB(255, 0, 255));     // фиолетовая призма

    // Вызываем Show() – теперь все рисуются корректно
    pt.Show();   getchar();
    ln.Show();   getchar();
    tr.Show();   getchar();
    pr.Show();   getchar();

    // Двигаем с помощью MoveTo – также работает правильно
    std::cout << "2. Перемещение объектов (MoveTo):\n";
    pt.MoveTo(300 + 350, 450); getchar();
    ln.MoveTo(250 + 350, 380); getchar();   // перемещается базовая точка, отрезок сдвигается
    tr.MoveTo(450 + 350, 350); getchar();
    pr.MoveTo(600 + 350, 400); getchar();

    // ---------- Часть 2: Перегруженные конструкторы ----------
    std::cout << "3. Конструкторы по умолчанию (объекты в левой части экрана):\n";

    // Создаём объекты конструкторами без параметров, затем задаём им нужные параметры
    Point pDef;               // (0,0, чёрный)
    Line lDef;                // (0,0)-(0,0), чёрный
    Triangle tDef;            // три вершины в (0,0)
    TriangularPrism prDef;    // всё в нулях

    // Присвоим им какие-нибудь координаты через сеттеры, чтобы увидеть на экране
    pDef.PutX(100); pDef.PutY(200); pDef.PutC(RGB(255, 255, 0)); // жёлтая точка
    lDef.PutX(100); lDef.PutY(150); lDef.PutX2(200); lDef.PutY2(250); lDef.PutC(RGB(0, 255, 255)); // голубой отрезок
    tDef.PutX(100); tDef.PutY(200); tDef.PutX2(200); tDef.PutY2(300);
    tDef.PutX3(150); tDef.PutY3(250); tDef.PutC(RGB(255, 128, 0)); // оранжевый треугольник
    prDef.PutX(80); prDef.PutY(300); prDef.PutX2(180); prDef.PutY2(350);
    prDef.PutX3(130); prDef.PutY3(400); prDef.PutHeight(60); prDef.PutC(RGB(128, 0, 255)); // сиреневая призма

    // Покажем их
    pDef.Show();    getchar();
    lDef.Show();    getchar();
    tDef.Show();    getchar();
    prDef.Show();   getchar();

    // Вычислим параметры
    std::cout << "\nГеометрические параметры:\n";
    std::cout << "Длина отрезка: " << ln.Length() << std::endl;
    std::cout << "Периметр треугольника: " << tr.Perimeter() << std::endl;
    std::cout << "Площадь треугольника: " << tr.Area() << std::endl;
    std::cout << "Объём призмы: " << pr.Volume() << std::endl;

    std::cout << "\nНажмите любую клавишу для завершения...";
    getchar();
    CloseWindow(hwnd);
    return 0;
}