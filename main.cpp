#include <iostream>
#include <windows.h>
#include <cmath>

using namespace std;

double mainFunction(double x) {
    return sin(x) * exp(-x);
    //return x;
}

double integrationLeftRectangle(double xmin, double xmax, double h) {
    double xi = xmin;
    double square = 0.0;
    while (xi + h < xmax) {
        square += fabs(mainFunction(xi)) * h;
        xi += h;
    }
    square += (xmax - xi) * fabs(mainFunction(xi));//исправил так, чтобы последний сегмент вычислялся отдельно+fabs
    return square;
}

double integrationRightRectangle(double xmin, double xmax, double h) {
    double xi = xmin + h;
    double square = 0.0;
    while (xi < xmax) {
        square += fabs(mainFunction(xi)) * h;
        xi += h;
    }
    square += (xmax - (xi - h)) * fabs(mainFunction(xmax));//исправил так, чтобы последний сегмент вычислялся отдельно
    return square;
}

double integrationTrapezoidal(double xmin, double xmax, double h) {
    double xi = xmin;
    double square = 0.0;
    while (xi < xmax - h) {
        square += (fabs(mainFunction(xi)) + fabs(mainFunction(xi + h))) ;
        xi += h;
    }
    square *= h;
    square += (fabs(mainFunction(xi)) + fabs(mainFunction(xmax))) * (xmax-xi);//исправлено
    //??? последняя площадь имеет высоту h*, не обязательно равную шагу h => считаем вне цикла
    return square/2;
}

double
precisionIntegration(double (*integrationMethod)(double, double, double), double xmin, double xmax, double precision) {

    int i = 1;
    double h = (xmax - xmin) / i;
    double result = 0.0;
    double prevResult = -1.0;
//uslovie 2
    while (fabs(prevResult - result) > precision && i < INT_MAX / 2) {
        prevResult = result;
        result = integrationMethod(xmin, xmax, h);
        i *= 2;
        h = (xmax - xmin) / i;
    }
    return result;
}

int mainOne() {
    cout << "Расчет интеграла без заданной точности" << endl;
    double xmin, xmax;
    int n;

    //cout << "Заданная функция `f(x) = x`.\nВведите xmin:" << endl;
    cout << "Заданная функция `sin(x) * exp(-x)`.\nВведите xmin:" << endl;
    cin >> xmin;
    cout << "Введите xmax:" << endl;
    cin >> xmax;
    cout << "Введите количество отрезков n:" << endl;
    cin >> n;

    double nn = n;
    double h = (xmax - xmin) / nn;
    cout << "Длина одного отрезка h = " << h << endl;
    double hlast = h * nn - (xmax - xmin);
    cout << "Длина остаточного отрезка hlast = " << hlast << endl;

    double result = 0;
    result = integrationLeftRectangle(xmin, xmax, h);
    cout << "Площадь по методу левых прямоугольников равна " << result << endl;
    result = integrationRightRectangle(xmin, xmax, h);
    cout << "Площадь по методу правых прямоугольников равна " << result << endl;
    result = integrationTrapezoidal(xmin, xmax, h);
    cout << "Площадь по методу трапеций равна " << result << endl;

    return 0;
}

int mainTwo() {
    cout << "Расчет интеграла с учетом заданной точности" << endl;
    double xmin, xmax;
    double precision;

    //cout << "Заданная функция `f(x) = x`.\nВведите xmin:" << endl;
    cout << "Заданная функция `sin(x) * exp(-x)`.\nВведите xmin:" << endl;
    cin >> xmin;
    cout << "Введите xmax:" << endl;
    cin >> xmax;
    cout << "Введите точность epsilon:" << endl;
    cin >> precision;

    double result = 0;
    result = precisionIntegration(integrationLeftRectangle, xmin, xmax, precision);
    cout << "Площадь по методу левых прямоугольников равна " << result << endl;
    result = precisionIntegration(integrationRightRectangle, xmin, xmax, precision);
    cout << "Площадь по методу правых прямоугольников равна " << result << endl;
    result = precisionIntegration(integrationTrapezoidal, xmin, xmax, precision);
    cout << "Площадь по методу трапеций равна " << result << endl;

    return 0;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int choose;
    cout << "Выберите режим работы 1 или 2: ";
    cin >> choose;
    switch (choose) {
        case 1: {
            mainOne();
            break;
        }
        case 2: {
            mainTwo();
            break;
        }
        default:
            cout << "Ошибка" << endl;
    }
    return 0;
}
