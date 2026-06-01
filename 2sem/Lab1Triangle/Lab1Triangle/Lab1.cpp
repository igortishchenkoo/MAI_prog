#include <windows.h>
#include <iostream>
#include <math.h>

HDC hdc;

class Triangle
{
private:
    short Xc, Yc;
    short R;
    float fi;
    size_t color;

public:
    Triangle(short Xc, short Yc, short R, float fi, size_t color);

    short GetXc();
    short GetYc();
    short GetR();
    float GetFi();

    void PutXc(short newXc);
    void PutYc(short newYc);
    void PutFi(float newFi);

    void Show();
    void Hide();

    void Rotate(float dfi);
    void Orbit(short Xext, short Yext, float dfi);
    void TidalLock(short Xext, short Yext, float dfi);
};

Triangle::Triangle(short Xc, short Yc, short R, float fi, size_t color)
{
    this->Xc = Xc;
    this->Yc = Yc;
    this->R = R;
    this->fi = fi;
    this->color = color;
}

short Triangle::GetXc() { return Xc; }
short Triangle::GetYc() { return Yc; }
short Triangle::GetR() { return R; }
float Triangle::GetFi() { return fi; }

void Triangle::PutXc(short newXc) { Xc = newXc; }
void Triangle::PutYc(short newYc) { Yc = newYc; }
void Triangle::PutFi(float newFi) { fi = newFi; }

void Triangle::Show()
{
    HPEN pen = CreatePen(PS_SOLID, 2, color);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    const float PI = 3.14159265f;

    const float baseAngle = 120.0f * PI / 180.0f;

    short X[3], Y[3];
    float vertAngle[3] = { fi, fi + baseAngle, fi + 2.0f * baseAngle };
    for (int i = 0; i < 3; i++)
    {
        X[i] = Xc + (short)(R * sin(vertAngle[i]));
        Y[i] = Yc - (short)(R * cos(vertAngle[i]));
    }
    MoveToEx(hdc, X[0], Y[0], NULL);
    LineTo(hdc, X[1], Y[1]);
    LineTo(hdc, X[2], Y[2]);
    LineTo(hdc, X[0], Y[0]);

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

void Triangle::Hide()
{
    size_t tempColor = color;
    color = RGB(241, 241, 241);
    Show();
    color = tempColor;
}

void Triangle::Rotate(float dfi)
{
    Hide();
    fi += dfi;
    Show();
}

void Triangle::Orbit(short Xext, short Yext, float dfi)
{
    Hide();

    short dx = Xc - Xext;
    short dy = Yc - Yext;

    float orbitAngle = atan2((float)dy, (float)dx);

    float orbitR = sqrt((float)(dx * dx + dy * dy));

    orbitAngle += dfi;

    Xc = Xext + (short)(orbitR * cos(orbitAngle));
    Yc = Yext + (short)(orbitR * sin(orbitAngle));

    Show();
}

void Triangle::TidalLock(short Xext, short Yext, float dfi)
{
    Hide();

    short dx = Xc - Xext;
    short dy = Yc - Yext;
    float orbitAngle = atan2((float)dy, (float)dx);
    float orbitR = sqrt((float)(dx * dx + dy * dy));
    orbitAngle += dfi;

    Xc = Xext + (short)(orbitR * cos(orbitAngle));
    Yc = Yext + (short)(orbitR * sin(orbitAngle));
    fi = atan2((float)(Xext - Xc), (float)(Yext - Yc));

    Show();
}

int main()
{
    system("color F0");

    HWND hwnd = GetConsoleWindow();
    if (hwnd == NULL) return 1;

    hdc = GetWindowDC(hwnd);
    if (hdc == NULL) return 1;

    short R = 60;

    Triangle T1(300, 200, R, 0.0f, RGB(0, 0, 255));
    Triangle T2(820, 400, R, 0.0f, RGB(0, 150, 0));
    Triangle T3(820, 700, R, 0.0f, RGB(255, 0, 0));

    short Xext2 = 700, Yext2 = 400;
    short Xext3 = 700, Yext3 = 700;

    float dfi = 0.05f;

    std::cout << "Lab 1 - Triangle (variant 7)" << std::endl;
    std::cout << "Press any key to start animation..." << std::endl;
    std::cout << "Hold SHIFT to stop." << std::endl;
    getchar();

    T1.Show();
    T2.Show();
    T3.Show();

    while (true)
    {
        T1.Rotate(dfi);
        T2.Orbit(Xext2, Yext2, dfi);
        T3.TidalLock(Xext3, Yext3, dfi);

        Sleep(30);

        if (GetKeyState(VK_SHIFT) < 0) break;
    }

    ReleaseDC(hwnd, hdc);

    return 0;
}
