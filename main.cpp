
// =============================================================
//  Лабораторна робота № 1 з дисципліни "Об'єктно-орієнтоване
//  програмування" (ООП)
//  Варіант № 15
//
//  Завдання 1. Розробити програму з використанням класів для
//  обчислення значень функцій a[x,y,z,b] і b[x,y,z]:
//    b[x,y,z] = (3x + sin^2( |x+z|^(1/3) / (2x+1.34) ))^2 - y*e^(x^2-z)
//    a[x,y,z,b] = (|x|^1.5 + sqrt(cos^2|x-b|^1.2)) / (3 + x^2 + sin^2(y+z)^3) + (3-x)/(y+z)
//    x = 0.48*No, y = 0.47*No, z = -1.32*No,  No = 15
//
//  Завдання 2. Використовуючи дані з завдання 1, виконати
//  одновимірне табулювання функцій a і b за змінною x:
//    xп = -1, xк = 1, крок dx = 0.2
//  Результат вивести за допомогою інструменту MultiLine
//  (у циклі виводити значення в багаторядкове текстове поле).
// =============================================================

#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>

class FunctionB {
    double x, y, z;

public:
    FunctionB(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    double calculate() const {
        double inner = pow(fabs(x + z), 1.0 / 3.0) / (2.0 * x + 1.34);
        double term1 = pow(3.0 * x + pow(sin(inner), 2), 2);
        double term2 = y * exp(x * x - z);
        return term1 - term2;
    }
};

class FunctionA {
    double x, y, z, b;

public:
    FunctionA(double x_, double y_, double z_, double b_)
        : x(x_), y(y_), z(z_), b(b_) {}

    double calculate() const {
        double numerator = pow(fabs(x), 1.5) +
                            sqrt(pow(cos(pow(fabs(x - b), 1.2)), 2));
        double denominator = 3.0 + x * x + pow(sin(pow(y + z, 3)), 2);
        double result = numerator / denominator + (3.0 - x) / (y + z);
        return result;
    }
};


class Tabulator {

    double xStart, xEnd, step;
    double y, z;
    std::ostringstream buffer;
public:
    Tabulator(double xStart_, double xEnd_, double step_, double y_, double z_)
        : xStart(xStart_), xEnd(xEnd_), step(step_), y(y_), z(z_) {}

    void run() {
        buffer << std::fixed << std::setprecision(6);
        buffer << std::setw(10) << "x"
               << std::setw(20) << "b[x,y,z]"
               << std::setw(20) << "a[x,y,z,b]" << "\n";
        buffer << std::string(50, '-') << "\n";

        const double eps = 1e-9;
        for (double x = xStart; x <= xEnd + eps; x += step) {
            FunctionB funcB(x, y, z);
            double bValue = funcB.calculate();

            FunctionA funcA(x, y, z, bValue);
            double aValue = funcA.calculate();

            buffer << std::setw(10) << x
                   << std::setw(20) << bValue
                   << std::setw(20) << aValue << "\n";
        }
    }


    std::string getText() const {
        return buffer.str();
    }
};

int main() {
    setlocale(LC_ALL, "");

    const int No = 15;
    double x = 0.48 * No;
    double y = 0.47 * No;
    double z = -1.32 * No;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "=== Завдання 1: обчислення a[x,y,z,b] i b[x,y,z] ===\n";
    std::cout << "Variant No = " << No << std::endl;
    std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;

    FunctionB funcB(x, y, z);
    double bValue = funcB.calculate();
    std::cout << "b[x,y,z] = " << bValue << std::endl;

    FunctionA funcA(x, y, z, bValue);
    double aValue = funcA.calculate();
    std::cout << "a[x,y,z,b] = " << aValue << std::endl;


    std::cout << "\n=== Завдання 2: табулювання функцій a i b за x ===\n";
    std::cout << "xп = -1, xк = 1, dx = 0.2 (вивід у MultiLine):\n";

    Tabulator table(-1.0, 1.0, 0.2, y, z);
    table.run();


    std::string multiLineText = table.getText();
    std::cout << multiLineText;

    return 0;
}