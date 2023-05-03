#include <iostream>
#include <stdexcept>
#include "sources/Fraction.hpp"

using namespace std;
using namespace ariel;

int main() {
    // Test constructor and basic operations
    Fraction a(3, 4);
    Fraction b(2, 5);
    Fraction c;
    Fraction d(8);
    Fraction e(0, 1);

    cout << "a: " << a << endl; // 3/4
    cout << "b: " << b << endl; // 2/5
    cout << "c: " << c << endl; // 0/1
    cout << "d: " << d << endl; // 8/1
    cout << "e: " << e << endl; // 0/1

    cout << "a+b: " << a + b << endl; // 23/20
    cout << "a-b: " << a - b << endl; // 7/20
    cout << "a*b: " << a * b << endl; // 3/10
    cout << "a/b: " << a / b << endl; // 15/8
    cout << "a+2: " << a + 2 << endl; // 11/4
    cout << "a-0.25: " << a - 0.25 << endl; // 1/2

    // Test comparison operators
    cout << (a == b) << endl; // 0
    cout << (a != b) << endl; // 1
    cout << (a > b) << endl; // 1
    cout << (a < b) << endl; // 0
    cout << (a >= b) << endl; // 1
    cout << (a <= b) << endl; // 0

    // Test increment and decrement operators
    cout << ++c << endl; // 1/1
    cout << c++ << endl; // 1/1
    cout << c << endl; // 2/1
    cout << --d << endl; // 7/1
    cout << d-- << endl; // 7/1
    cout << d << endl; // 6/1

    // Test exception handling
    try {
        Fraction f(2, 0);
    } catch (const std::exception &e) {
        cout << "Exception caught: " << e.what() << endl; // Exception caught: Denominator cannot be zero
    }

    return 0;
}