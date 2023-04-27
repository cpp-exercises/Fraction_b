#include "doctest.h"
#include <stdexcept>
#include "sources/Fraction.hpp"
#include <iostream>
#include <algorithm> // For __gcd; taken from the internet
#include <typeinfo> // For typeid(...)
#include <sstream>
using namespace ariel;
using namespace std;

TEST_CASE("Fraction object initialization & Getters return expected values") {
    Fraction a(1, 2);

    // Check that the type of numerator and denominator are int
    CHECK(typeid(a.getNumerator()).name() == typeid(int).name());
    CHECK(typeid(a.getDenominator()).name() == typeid(int).name());

    // Check that the int constractor's fields are like expected. Also checks the getters
    CHECK(((a.getNumerator() == 1) && (a.getDenominator() == 2)));

    // Check that the float constractor's fields are like expected
    Fraction b(0.3333);
    CHECK(((b.getNumerator() == 333) && (b.getDenominator() == 1000)));

    // Check that a Fraction can't be created if denominator is 0
    CHECK_THROWS(Fraction(1,0));
}

TEST_CASE("Fraction addition test") {
    Fraction a(1, 2), b(1, 4); 
    Fraction c = a + b; // 1/2 + 1/4 = 3/4
    CHECK(((c.getNumerator() == 3) && (c.getDenominator() == 4)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1); // Reduced as possible


    Fraction d(1, 5);
    float e = 0.4; // Will be converted to 2/5
    Fraction f = d + e; // 1/5 + 2/5 = 3/5
    CHECK(((f.getNumerator() == 3) && (f.getDenominator() == 5)));
    CHECK(__gcd(f.getNumerator(), f.getDenominator()) == 1);


    Fraction g = e + d;
    CHECK(((g.getNumerator() == 3) && (g.getDenominator() == 5)));
    CHECK(__gcd(g.getNumerator(), g.getDenominator()) == 1);
}

TEST_CASE("Fraction subtraction test") {
    Fraction a(1, 2), b(1, 4);
    Fraction c = a - b;
    CHECK(((c.getNumerator() == 1) && (c.getDenominator() == 4)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
    
    Fraction d(4, 5);
    float e = 0.4;
    Fraction f = d - e; // 4/5 - 2/5 = 2/5
    CHECK(((f.getNumerator() == 2) && (f.getDenominator() == 5)));
    CHECK(__gcd(f.getNumerator(), f.getDenominator()) == 1);

    Fraction g = e - d; // 2/5 - 4/5 = -2/5
    CHECK(((g.getNumerator() == -2) && (g.getDenominator() == 5)));
    CHECK(__gcd(g.getNumerator(), g.getDenominator()) == 1);
}

TEST_CASE("Fraction multiplication test") {
    Fraction a(1, 2), b(1, 4);
    Fraction c = a * b;
    CHECK(((c.getNumerator() == 1) && (c.getDenominator() == 8)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
    
    Fraction d(4, 5);
    float e = 0.4;
    Fraction f = d * e; // 4/5 * 2/5 = 8/25
    CHECK(((f.getNumerator() == 8) && (f.getDenominator() == 25)));
    CHECK(__gcd(f.getNumerator(), f.getDenominator()) == 1);

    Fraction g = e * d; // 2/5 * 4/5 = 8/25
    CHECK(((g.getNumerator() == 8) && (g.getDenominator() == 25)));
    CHECK(__gcd(g.getNumerator(), g.getDenominator()) == 1);
}

TEST_CASE("Fraction division test") {
    Fraction a(1, 2), b(1, 4);
    Fraction c = a / b; // 1/2 / 1/4 = 1/2 * 4/1 = 4/2 = 2/1
    CHECK(((c.getNumerator() == 2) && (c.getDenominator() == 1)));
    CHECK(__gcd(c.getNumerator(), c.getDenominator()) == 1);
    
    Fraction d(4, 5);
    float e = 0.4;
    Fraction f = d / e; // 4/5 / 2/5 = 4/5 * 5/2 = 20 / 10 = 2/1
    CHECK(((f.getNumerator() == 2) && (f.getDenominator() == 1)));
    CHECK(__gcd(f.getNumerator(), f.getDenominator()) == 1);

    Fraction g = e / d; // 2/5 / 4/5 = 2/5 * 5/4 = 10 / 20 = 1/2
    CHECK(((g.getNumerator() == 1) && (g.getDenominator() == 2)));
    CHECK(__gcd(g.getNumerator(), g.getDenominator()) == 1);
}

TEST_CASE("Division by zero throws an exception") {
    Fraction a(1, 2);
    CHECK_THROWS(a / 0);
}

// Using CHECK_FALSE during (<,>,<=,>=,==) to avoid things like auto-true
TEST_CASE("Fraction < comparison operator") {
    Fraction a(1, 2);
    Fraction b(1, 4);
    
    CHECK(b < a);
    CHECK_FALSE(b >= a); 
    CHECK(0.3 < a);
    CHECK_FALSE(0.3 >= a);
    CHECK(a < 1);
    CHECK_FALSE(a >= 1);
}

TEST_CASE("Fraction <= comparison operator") {
    Fraction a(1, 2);
    Fraction b(1, 4);
    
    CHECK(b <= a);
    CHECK_FALSE(b > a);
    CHECK(0.5 <= a);
    CHECK_FALSE(0.5 > a);
    CHECK(a <= 1);
    CHECK_FALSE(a > 1);
}

TEST_CASE("Fraction > comparison operator") {
    Fraction a(1, 2), b(1, 4);
    
    CHECK(a > b);
    CHECK_FALSE(a <= b);
    CHECK(a > 0.3);
    CHECK_FALSE(a <= 0.3);
    CHECK(1 > a);
    CHECK_FALSE(1 <= a);

}

TEST_CASE("Fraction >= comparison operator") {
    Fraction a(1, 2);
    Fraction b(1, 4);
    
    CHECK(a >= b);
    CHECK_FALSE(a < b);
    CHECK(a >= 0.3);
    CHECK_FALSE(a < 0.3);
    CHECK(1 >= a);
    CHECK_FALSE(1 < a);
}

TEST_CASE("Fraction == comparison operator") {
    Fraction a(1, 2);
    Fraction b(1, 4);
    Fraction c(2, 4); // Equivalent to 1/2
    Fraction d(1, 4);

    CHECK(b == d); // Pure equality
    CHECK(a == c); // Reduced equality
    CHECK_FALSE(a == b);
    CHECK(a == 0.5);
    CHECK_FALSE(a == 0.3);
    CHECK(0.5 == a);
    CHECK_FALSE(0.3 == a);
    CHECK(b == d);
}

TEST_CASE("Prefix and postfix increment operators on Fraction class") {
    Fraction a(1, 2);

    // Use prefix increment operator on Fraction object
    Fraction b = ++a;
    // Check that the value of a has been incremented to 3/2
    CHECK(a.getNumerator() == 3);
    CHECK(a.getDenominator() == 2);
    // Check that the value of b is also 3/2
    CHECK(b.getNumerator() == 3);
    CHECK(b.getDenominator() == 2);

    a = Fraction(1, 2); // Reset

    // Use postfix increment operator on Fraction object
    Fraction c = a++;
    // Check that the value of a has been incremented to 3/2
    CHECK(a.getNumerator() == 3);
    CHECK(a.getDenominator() == 2);
    // Check that the value of c is still 1/2
    CHECK(c.getNumerator() == 1);
    CHECK(c.getDenominator() == 2);
}

TEST_CASE("Prefix and postfix decrement operators on Fraction class") {
    Fraction a(3, 2);

    // Use prefix decrement operator on Fraction object
    Fraction b = --a;
    // Check that the value of a has been decremented to 1/2
    CHECK(a.getNumerator() == 1);
    CHECK(a.getDenominator() == 2);
    // Check that the value of b is also 1/2
    CHECK(b.getNumerator() == 1);
    CHECK(b.getDenominator() == 2);

    a = Fraction(3, 2); // Reset

    // Use postfix decrement operator on Fraction object
    Fraction c = a--;
    // Check that the value of a has been decremented to 1/2
    CHECK(a.getNumerator() == 1);
    CHECK(a.getDenominator() == 2);
    // Check that the value of c is still 3/2
    CHECK(c.getNumerator() == 3);
    CHECK(c.getDenominator() == 2);
}

TEST_CASE("Output and Input Stream Operators") {
    Fraction a(1, 2), b(3, 4);
    ostringstream os;

    // Test operator<<
    CHECK_NOTHROW(os << a); // Not thrwoing error
    CHECK(os.str() == "1/2"); // Prints well

    istringstream is("5 6"); // Could also be "5,6" for ex
    istringstream bad_is("7");

    // Test operator>>
    CHECK_NOTHROW(is >> b);
    CHECK(b.getNumerator() == 5);
    CHECK(b.getDenominator() == 6);
    CHECK_THROWS(bad_is >> b); // Throws cuz the input is one number
}

TEST_CASE("Rounding of float numbers during arithmetic operations with Fractions") {
    Fraction a(2, 5);
    float b = 0.2001; // During the "+" operation it'll became 0.200, which is 1/5
    Fraction c = a + b; // 2/5 + 1/5 = 3/5
    CHECK(((c.getNumerator() == 3) && (c.getDenominator() == 5)));

    b = 0.2001;
    c = a - b; // 1/5
    CHECK(((c.getNumerator() == 1) && (c.getDenominator() == 5)));

    b = 0.2001;
    c = a * b; // 2/25
    CHECK(((c.getNumerator() == 2) && (c.getDenominator() == 25)));

    b = 0.2001;
    c = a / b; // 2/1
    CHECK(((c.getNumerator() == 2) && (c.getDenominator() == 1)));
}
