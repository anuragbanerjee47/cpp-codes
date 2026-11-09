#include <iostream>
#include <cmath>
using namespace std;

float AREA(float r)
{
    return 3.14159 * r * r;
}

float AREA(float l, float b)
{
    return l * b;
}

float AREA(float a, float b, float c)
{
    float s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main()
{
    float r, l, b, a, x, y;
    cout << "Enter radius of circle: ";
    cin >> r;
    cout << "Area of Circle = " << AREA(r) << endl;

    cout << "\nEnter length and breadth of rectangle: ";
    cin >> l >> b;
    cout << "Area of Rectangle = " << AREA(l, b) << endl;

    cout << "\nEnter three sides of triangle: ";
    cin >> a >> x >> y;
    cout << "Area of Triangle = " << AREA(a, x, y) << endl;

    return 0;
}