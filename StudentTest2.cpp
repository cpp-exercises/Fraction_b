#include <sstream>
#include "doctest.h"
#include "sources/Fraction.hpp"
#include <limits>
#include <vector>

using namespace std;
using namespace ariel;

TEST_SUITE("Fraction constructors tests") {

    TEST_CASE("Parameterized constructor with zero numerator") {
        CHECK_NOTHROW(Fraction frac{0, 4});
        CHECK_NOTHROW(Fraction frac{0, -4});

    }

    TEST_CASE("Parameterized constructor with zero denominator") {
        CHECK_THROWS_AS(Fraction frac(3, 0), std::invalid_argument);
        CHECK_THROWS_AS(Fraction frac(-4, 0), std::invalid_argument);
    }

    TEST_CASE("Parameterized constructor with regular arguments") {
        Fraction frac1{3, 4};
        CHECK_EQ(frac1, Fraction{3, 4});

        Fraction frac2{30, -60};
        CHECK_EQ(frac2, Fraction{-1, 2});
    }
}

TEST_SUITE("Overloaded == operator tests") {

    TEST_CASE("Basic equality tests") {
        Fraction frac1{2, 3};
        Fraction frac2{4, 6};
        CHECK_EQ(frac1, frac2);
    }

    TEST_CASE("Sign variations") {
        Fraction frac1{-1, 5};
        Fraction frac2{1, -5};
        Fraction frac3{17, 19};
        Fraction frac4(-17, -19);
        CHECK_EQ(frac1, frac2);
        CHECK_EQ(frac3, frac4);
    }

    TEST_CASE("Different numerators and denominators") {
        Fraction frac1(11, 13);
        Fraction frac2(11, 15);
        Fraction frac3(12, 13);
        CHECK_NE(frac1, frac2);
        CHECK_NE(frac1, frac3);
    }

    TEST_CASE("Reduced form equality") {
        Fraction frac1(6, 18);
        Fraction frac2(2, 6);
        Fraction frac3(10, 30);
        CHECK_EQ(frac1, frac2);
        CHECK_EQ(frac1, frac3);
    }

    TEST_CASE("Zero representations") {
        Fraction frac1(0, 1);
        Fraction frac2(0, -3);
        Fraction frac3(-0, 4);
        CHECK_EQ(frac1, frac2);
        CHECK_EQ(frac1, frac3);
    }

    TEST_CASE("Equality with floating numbers") {
        Fraction frac1{1, 2};
        Fraction frac2{12963, 1000};
        CHECK_EQ(frac1, 0.5);
        CHECK_EQ(12.963, frac2);
        CHECK_NE(frac1, 12.963);
        CHECK_NE(0.5, frac2);
    }
}


TEST_SUITE("Overloaded <= and >= operators tests") {
    TEST_CASE("Fraction comparisons") {
        Fraction frac1{2, 3};
        Fraction frac2{1, 2};
        Fraction frac3{5, 6};
        Fraction frac4{-1, 5};
        Fraction frac5{17, 19};
        Fraction frac6{-17, -19};
        Fraction frac7{6, 18};
        Fraction frac8{2, 6};
        Fraction frac9{0, 1};
        Fraction frac10{7, 5};
        Fraction frac11{4,3};

        SUBCASE(">= operator test") {
            CHECK_GE(frac1, frac2);
            CHECK_GE(frac3, frac1);
            CHECK_GE(frac5, frac6);
            CHECK_GE(frac7, frac8);
            CHECK_GE(frac9, frac9);
            CHECK_GE(frac10, frac11);
            CHECK_FALSE((frac4 >= frac1));
            CHECK_FALSE((frac1 >= frac3));
        }

        SUBCASE("<= operator test") {
            CHECK_LE(frac2, frac1);
            CHECK_LE(frac1, frac3);
            CHECK_LE(frac6, frac5);
            CHECK_LE(frac8, frac7);
            CHECK_LE(frac9, frac9);
            CHECK_LE(frac11, frac10);
            CHECK_FALSE((frac1 <= frac4));
            CHECK_FALSE((frac3 <= frac1));
        }
    }

    TEST_CASE("Fraction comparison with floating point numbers") {
        Fraction frac1{1, 2};
        Fraction frac2{3, 4};
        double float_num1 = 0.5;
        double float_num2 = 0.75;

        SUBCASE(">= operator test") {
            CHECK_GE(frac1, float_num1);
            CHECK_GE(frac2, float_num2);
            CHECK_GE(frac2, float_num1);
            CHECK_FALSE((frac1 >= float_num2));
        }

        SUBCASE("<= operator test") {
            CHECK_LE(frac1, float_num1);
            CHECK_LE(frac2, float_num2);
            CHECK_LE(frac1, float_num2);
            CHECK_FALSE((frac2 <= float_num1));
        }
    }
}

TEST_SUITE("Overloaded < and > operators tests") {
    TEST_CASE("Fraction comparisons") {
        Fraction frac1{2, 3};
        Fraction frac2{1, 2};
        Fraction frac3{4, 5};
        Fraction frac4{1, 4};
        Fraction frac5{-4, 5};
        Fraction frac6{300, 500};
        Fraction frac7{1200, 2400};

        double complex_num1 = 4.321;
        double complex_num2 = -3.141;

        SUBCASE("Less than test") {
            CHECK_LT(frac2, frac1);
            CHECK_LT(frac4, frac1);
            CHECK_LT(frac5, frac2);
            CHECK_LT(frac6, frac3);
            CHECK_LT(frac7, frac6);
            CHECK_LT(frac1, complex_num1);
            CHECK_LT(complex_num2, frac5);
            CHECK_FALSE((frac1 < frac2));
            CHECK_FALSE((frac6 < frac7));
        }

        SUBCASE("Greater than test") {
            CHECK_GT(frac1, frac2);
            CHECK_GT(frac1, frac4);
            CHECK_GT(frac3, frac2);
            CHECK_GT(frac3, frac6);
            CHECK_GT(frac6, frac7);
            CHECK_GT(complex_num1, frac1);
            CHECK_GT(frac5, complex_num2);
            CHECK_FALSE((frac2 > frac1));
            CHECK_FALSE((frac7 > frac6));
        }
    }

    TEST_CASE("Other fraction comparisons") {
        std::vector<std::pair<Fraction, Fraction>> fracs = {
                {Fraction{2, 6}, Fraction{1, 2}},
                {Fraction{1000, 3000}, Fraction{1, 2}},
                {Fraction{1, 4}, Fraction{1, 3}},
                {Fraction{1, 3}, Fraction{2, 3}},
                {Fraction{1000, 3000}, Fraction{2, 3}},
                {Fraction{-1, 2}, Fraction{-1, 3}},
                {Fraction{1, -2}, Fraction{-1, 3}},
                {Fraction{3, -5}, Fraction{-2, 5}},
                {Fraction{-500, 1000}, Fraction{1000, -3000}},
                {Fraction{4, 3}, Fraction{7, 5}},
                {Fraction{7, 5}, Fraction{4, 2}},
                {Fraction{7, 5}, Fraction{9, 4}},
                {Fraction{120, 3}, Fraction{250, 3}}
        };

        for (size_t i = 0; i < fracs.size(); i++) {
            CHECK_LT(fracs[i].first, fracs[i].second);
            CHECK_FALSE((fracs[i].second < fracs[i].first));
            CHECK_GT(fracs[i].second, fracs[i].first);
            CHECK_FALSE((fracs[i].first > fracs[i].second));
        }
    }
}

TEST_SUITE("Overloaded + and - operator tests") {

    TEST_CASE("Basic addition and subtraction") {
        // Small fractions
        CHECK_EQ(Fraction{1, 4} + Fraction{1, 4}, Fraction{1, 2});
        CHECK_EQ(Fraction{2, 5} - Fraction{1, 3}, Fraction{1, 15});

        // Big fractions
        CHECK_EQ(Fraction{123, 250} + Fraction{123, 300}, Fraction{451, 500});
        CHECK_EQ(Fraction{-123, 250} - Fraction{127, 300}, Fraction{-1373, 1500});

        // Negative in numerator
        CHECK_EQ(Fraction{-3, 7} + Fraction{5, 14}, Fraction{-1, 14});
        CHECK_EQ(Fraction{-3, 7} - Fraction{5, 14}, Fraction{-11, 14});

        // Negative in denominator
        CHECK_EQ(Fraction{5, -7} + Fraction{3, -14}, Fraction{13, -14});
        CHECK_EQ(Fraction{5, -7} - Fraction{3, 14}, Fraction{13, -14});

        // Negative in both
        CHECK_EQ(Fraction{-5, -7} + Fraction{-3, -14}, Fraction{13, 14});
        CHECK_EQ(Fraction{-5, -7} - Fraction{-3, -14}, Fraction{1, 2});

        // Reduced and expanded fractions
        CHECK_EQ(Fraction{3, 6} + Fraction{1, 2}, Fraction{1, 1});
        CHECK_EQ(Fraction{10, 30} - Fraction{2, 3}, Fraction{-1, 3});

        // Adding and subtracting integers
        CHECK_EQ(Fraction{3, 1} + Fraction{-4, 1}, Fraction{-1, 1});
        CHECK_EQ(Fraction{5, 1} - Fraction{2, 1}, Fraction{3, 1});

        // Different numerator and same denominator
        CHECK_EQ(Fraction{3, 7} + Fraction{2, 7}, Fraction{5, 7});
        CHECK_EQ(Fraction{6, 11} - Fraction{3, 11}, Fraction{3, 11});

        // Adding and subtracting a combination of integers and fractions
        CHECK_EQ(Fraction{3, 1} + Fraction{2, 3}, Fraction{11, 3});
        CHECK_EQ(Fraction{-4, 1} - Fraction{5, 6}, Fraction{-29, 6});
    }

    TEST_CASE("Subtracting a negative fraction") {
        CHECK_EQ(Fraction{2, 5} - Fraction{-1, 3}, Fraction{11, 15});
        CHECK_EQ(Fraction{3, 7} - Fraction{2, -5}, Fraction{29, 35});
        CHECK_EQ(Fraction{1, 4} - Fraction{-1, 2}, Fraction{6, 8});
        CHECK_EQ(Fraction{3, 2} - Fraction{1, -2}, Fraction{2, 1});
        CHECK_EQ(Fraction{1, 2} - Fraction{-5, 2}, Fraction{3, 1});
    }

    TEST_CASE("Adding and subtracting zero to a fraction, both as a fraction and as a floating point") {
        Fraction f1{2, 5};

        // Adding zero as a fraction
        CHECK_EQ(f1 + Fraction{0, 5}, f1);

        // Adding zero as a floating point from left
        CHECK_EQ(f1 + 0.0, f1);

        // Adding zero as a floating point from right
        CHECK_EQ(0.0 + f1, f1);

        // Subtracting zero as a fraction
        CHECK_EQ(f1 - Fraction{0, 5}, f1);

        // Subtracting zero as a floating point
        CHECK_EQ(f1 - 0.0, f1);


        // Subtracting a fraction from zero
        CHECK_EQ(0.0 - f1, Fraction{-2, 5});
    }

    TEST_CASE("Adding and subtracting floating-point variables from both sides") {

        // Adding a fraction to a simple floating-point number
        CHECK_EQ(Fraction{1, 2} + 0.5, Fraction{1, 1});
        CHECK_EQ(Fraction{1, 4} + 0.75, Fraction{5, 5});

        // Adding a fraction to a complex floating-point number
        CHECK_EQ(Fraction{1, 3} + 4.321, 4.654);
        CHECK_EQ(Fraction{2, 5} + 3.678, Fraction{2039, 500});

        // Subtracting a simple floating-point number from a fraction
        CHECK_EQ(Fraction{1, 2} - 0.25, Fraction{2, 8});
        CHECK_EQ(Fraction{3, 4} - 0.5, Fraction{1, 4});

        // Subtracting a complex floating-point number from a fraction
        CHECK_EQ(Fraction{7, 2} - 1.321, Fraction{2179, 1000});
        CHECK_EQ(Fraction{9, 4} - 0.678, Fraction{393, 250});

        // Subtracting a fraction from a simple floating-point number
        CHECK_EQ(1.5 - Fraction{1, 2}, Fraction{1, 1});
        CHECK_EQ(1.0 - Fraction{1, 4}, Fraction{3, 4});

        // Subtracting a fraction from a complex floating-point number
        CHECK_EQ(5.321 - Fraction{2, 3}, Fraction{2327, 500});
        CHECK_EQ(3.678 - Fraction{3, 4}, Fraction{366, 125});

        // Adding a simple floating-point number to a fraction (simple)
        CHECK_EQ(0.5 + Fraction{1, 2}, 1.0);
        CHECK_EQ(0.75 + Fraction{1, 5}, Fraction{19, 20});

        // Adding a complex floating-point number to a fraction
        CHECK_EQ(4.321 + Fraction{1, 3}, Fraction{2327, 500});
        CHECK_EQ(3.678 + Fraction{2, 5}, Fraction{2039, 500});
    }

    TEST_CASE("Inequality checks for fractions") {
        CHECK_NE(Fraction{1, 2} + Fraction{1, 4}, Fraction{1, 2});
        CHECK_NE(Fraction{2, 5} - Fraction{1, 3}, Fraction{1, 6});

        CHECK_NE(Fraction{3, 1} + Fraction{2, 3}, Fraction{4, 1});
        CHECK_NE(Fraction{-4, 1} - Fraction{5, 6}, Fraction{-2, 1});
    }

    TEST_CASE("Inequality checks with floating-point numbers and fractions") {
        // Check for inequality when adding a fraction to a floating-point number (simple)
        CHECK_NE(Fraction{1, 2} + 0.5, 0.75);

        // Check for inequality when adding a fraction to a complex floating-point number
        CHECK_NE(Fraction{1, 3} + 4.321, 5.0);

        // Check for inequality when subtracting a simple floating-point number from a fraction
        CHECK_NE(Fraction{1, 2} - 0.25, 0.5);

        // Check for inequality when subtracting a complex floating-point number from a fraction
        CHECK_NE(Fraction{7, 2} - 1.321, 3.0);

        // Check for inequality when subtracting a fraction from a simple floating-point number
        CHECK_NE(1.5 - Fraction{1, 2}, 1.25);

        // Check for inequality when subtracting a fraction from a complex floating-point number
        CHECK_NE(5.321 - Fraction{2, 3}, 4.5);

        // Check for inequality when adding a simple floating-point number to a fraction
        CHECK_NE(0.5 + Fraction{1, 2}, 1.25);

        // Check for inequality when adding a complex floating-point number to a fraction
        CHECK_NE(4.321 + Fraction{1, 3}, 5.0);
    }
}

TEST_SUITE("Overloaded * operator tests") {

    TEST_CASE("Basic multiplication tests") {
        CHECK_EQ(Fraction{2, 5} * Fraction{3, 5}, Fraction{6, 25});
        CHECK_EQ(Fraction{2, 3} * Fraction{4, -5}, Fraction{8, -15});
        CHECK_EQ(Fraction{-2, 5} * Fraction{3, 5}, Fraction{-6, 25});
        CHECK_EQ(Fraction{3, -4} * Fraction{-5, 6}, Fraction{15, 24});
        CHECK_EQ(Fraction{-3, -4} * Fraction{-5, 6}, Fraction{-15, 24});
        CHECK_EQ(Fraction{7, 4} * Fraction{4, 3}, Fraction{700, 300});
    }

    TEST_CASE("Multiplying fractions by one") {
        // Fraction equivalent of one
        CHECK_EQ(Fraction{3, 5} * Fraction{1, 1}, Fraction{3, 5});
        CHECK_EQ(Fraction{5, 5} * Fraction{-8, 14}, Fraction{4, -7});

        // Floating number
        CHECK_EQ(Fraction{3, 5} * 1.0, Fraction{3, 5});
        CHECK_EQ(1 * Fraction{-8, 14}, Fraction{4, -7});
    }

    TEST_CASE("Multiplying fractions by zero") {
        //By a fraction
        CHECK_EQ(Fraction{6, 10} * Fraction{0, 10000}, Fraction{0, 1});
        CHECK_EQ(Fraction{0, 1} * Fraction{-4, 7}, Fraction{0, -1});

        //By a floating point number
        CHECK_EQ(Fraction{6, 10} * 0.0, Fraction{0, 1});
        CHECK_EQ(0 * Fraction{-4, 7}, Fraction{0, -1});
    }

    TEST_CASE("Multiplying fractions with floating-point numbers") {
        // From left
        CHECK_EQ(Fraction{2, 3} * 0.5, Fraction{1, 3});
        CHECK_EQ(0.5 * Fraction{2, 3}, Fraction{1, 3});

        //From right
        CHECK_EQ(Fraction{3, 4} * 0.8, Fraction{3, 5});
        CHECK_EQ(0.8 * Fraction{3, 4}, Fraction{3, 5});

        //More complex floating point numbers
        CHECK_EQ(4.321 * Fraction{1, 3}, Fraction{4321, 3000});
        CHECK_EQ(Fraction{2, 5} * 3.678, Fraction{1839, 1250});
    }

    TEST_CASE("Multiplying big fractions") {
        CHECK_EQ(Fraction{999, 1000} * Fraction{999, 1000}, Fraction{998001, 1000000});
        CHECK_EQ(Fraction{12345, 23456} * Fraction{34567, 45678}, Fraction{426920715, 1072143816});
    }

    TEST_CASE("Inequality checks with floating-point numbers and fractions") {
        // Check for inequality when multiplying a fraction by a fraction (simple)
        CHECK_NE(Fraction{1, 2} * Fraction{1, 3}, Fraction{3, 5});
        CHECK_NE(Fraction{3, 4} * Fraction{3, 5}, Fraction{5, 9});

        // Check for inequality when multiplying a fraction by a simple floating-point number
        CHECK_NE(Fraction{2, 3} * 0.5, Fraction{2, 3});
        CHECK_NE(Fraction{3, 4} * 0.8, Fraction{9, 8});

        // Check for inequality when multiplying a simple floating-point number by a fraction
        CHECK_NE(0.5 * Fraction{2, 3}, Fraction{3, 2});
        CHECK_NE(0.8 * Fraction{3, 4}, Fraction{4, 3});

        // Check for inequality when multiplying a fraction by a complex floating-point number
        CHECK_NE(Fraction{2, 3} * 4.321, Fraction{2, 3} * 4);
        CHECK_NE(Fraction{3, 4} * 3.678, Fraction{3, 4} * 4);

        // Check for inequality when multiplying a complex floating-point number by a fraction
        CHECK_NE(4.321 * Fraction{1, 3}, 4.321 * Fraction{1, 4});
        CHECK_NE(3.678 * Fraction{2, 5}, 3.678 * Fraction{2, 6});

        // Check for inequality when multiplying big fractions
        CHECK_NE(Fraction{999, 1000} * Fraction{999, 1000}, Fraction{9999000, 1000000});
        CHECK_NE(Fraction{12345, 23456} * Fraction{34567, 45678}, Fraction{426920715, 900000000});
    }
}

TEST_SUITE("Overloaded / operator tests") {

    TEST_CASE("Basic division tests") {
        CHECK_EQ(Fraction{2, 5} / Fraction{3, 5}, Fraction{2, 3});
        CHECK_EQ(Fraction{1, 4} / Fraction{3, 4}, Fraction{1, 3});
        CHECK_EQ(Fraction{2, 3} / Fraction{4, -5}, Fraction{-30, 36});
        CHECK_EQ(Fraction{-3, 4} / Fraction{5, 6}, Fraction{-9, 10});
        CHECK_EQ(Fraction{-2, 5} / Fraction{3, 5}, Fraction{-2, 3});
        CHECK_EQ(Fraction{3, -4} / Fraction{-5, 6}, Fraction{9, 10});
        CHECK_EQ(Fraction{-3, -4} / Fraction{-5, 6}, Fraction{-9, 10});
        CHECK_EQ(Fraction{3, 2} / Fraction{5, 4}, Fraction{6, 5});
        CHECK_EQ(Fraction{7, 4} / Fraction{4, 3}, Fraction{21, 16});

        // Inequality checks when dividing a fraction by a fraction
        CHECK_NE(Fraction{1, 2} / Fraction{1, 3}, Fraction{3, 5});
        CHECK_NE(Fraction{3, 4} / Fraction{3, 5}, Fraction{5, 9});
    }

    TEST_CASE("Dividing fractions by one and dividing one by a fraction") {
        CHECK_EQ(Fraction{3, 5} / Fraction{1, 1}, Fraction{3, 5});
        CHECK_EQ(Fraction{-8, 14} / Fraction{5, 5}, Fraction{-4, 7});

        CHECK_EQ(Fraction{1, 1} / Fraction{7, 4}, Fraction{4, 7});
        CHECK_EQ(Fraction{-1, 1} / Fraction{4, 7}, Fraction{-7, 4});

        CHECK_NE(Fraction{-1, 1} / Fraction{4, 7}, Fraction{7, 4});
    }

    TEST_CASE("Dividing fractions by zero and dividing zero by a fraction") {
        CHECK_THROWS_AS((Fraction{6, 10} / Fraction{0, 10000}), std::runtime_error);
        CHECK_THROWS_AS((Fraction{-4, 7} / 0.0), std::runtime_error);

        CHECK_EQ(Fraction{0, 1} / 5.585, Fraction{0, 3});
        CHECK_EQ(0.0 / Fraction{1, 2}, Fraction{0, 3});
    }

    TEST_CASE("Dividing fractions and floating-point numbers with equality and inequality checks") {
        // Equality checks when dividing a fraction by a floating-point number
        CHECK_EQ(Fraction{2, 3} / 0.5, Fraction{4, 3});
        CHECK_EQ(Fraction{3, 4} / 0.8, Fraction{15, 16});

        // Equality checks when dividing a floating-point number by a fraction
        CHECK_EQ(0.5 / Fraction{2, 3}, Fraction{3, 4});
        CHECK_EQ(-0.8 / Fraction{3, 4}, Fraction{-16, 15});

        // Equality checks when dividing a floating-point number by a fraction, incorporating negatives
        CHECK_EQ(Fraction{-2, 3} / 0.57, Fraction{-200, 171});
        CHECK_EQ(Fraction{3, -4} / -0.82, Fraction{75, 82});


        // Equality checks when dividing a floating-point number by a fraction, incorporating negatives
        CHECK_EQ(4.321 / Fraction{1, 3}, Fraction{12963, 1000});
        CHECK_EQ(-4.321 / Fraction{1, 3}, Fraction{-12963, 1000});

        // Inequality checks when dividing a fraction by a simple floating-point number
        CHECK_NE(Fraction{2, 3} / 0.5, Fraction{2, 3});
        CHECK_NE(Fraction{3, 4} / 0.8, Fraction{9, 8});

        // Inequality checks when dividing a simple floating-point number by a fraction
        CHECK_NE(0.5 / Fraction{2, 3}, Fraction{3, 2});
        CHECK_NE(0.8 / Fraction{3, 4}, Fraction{4, 3});

        // Inequality checks when dividing a fraction by a more complex floating-point number
        CHECK_NE(Fraction{2, 3} / 4.321, Fraction{2, 3} / 4);
        CHECK_NE(Fraction{3, 4} / 3.678, Fraction{3, 4} / 4);

        // Inequality checks when dividing a more complex floating-point number by a fraction
        CHECK_NE(4.321 / Fraction{1, 3}, 4.321 / Fraction{1, 4});
        CHECK_NE(3.678 / Fraction{2, 5}, 3.678 / Fraction{2, 6});
    }

    TEST_CASE("Dividing big fractions") {
        CHECK_EQ(Fraction{999, 1000} / Fraction{999, 1000}, Fraction{1, 1});
        CHECK_EQ(Fraction{12345, 23456} / Fraction{34567, 45678}, Fraction{281947455, 405401776});

        // Check for inequality when dividing big fractions
        CHECK_NE(Fraction{999, 1000} / Fraction{999, 1000}, Fraction{999, 2000});
        CHECK_NE(Fraction{12345, 23456} / Fraction{34567, 45678}, Fraction{564344010, 900000000});
    }
}

TEST_SUITE("Chaining operations and field characteristics") {

    TEST_CASE("Chaining mixed operations with floating-point numbers") {
        CHECK_EQ(Fraction{1, 3} * 3.0 + Fraction{1, 2}, Fraction{3, 2});
        CHECK_NE(Fraction{1, 3} * 3.0 + Fraction{1, 2}, Fraction{7, 2});

        CHECK_EQ(Fraction{2, 3} * 1.5 - Fraction{1, 4}, Fraction{3, 4});
        CHECK_NE(Fraction{2, 3} * 1.5 - Fraction{1, 4}, Fraction{1, 2});

        CHECK_EQ(0.5 * Fraction{3, 4} + Fraction{1, 4} * 2.0, Fraction{7, 8});
        CHECK_NE(0.5 * Fraction{3, 4} + Fraction{1, 4} * 2.0, Fraction{1, 2});

        CHECK_EQ((Fraction{2, 5} * 5.0) / (Fraction{1, 3} * 0.6), Fraction{10, 1});
        CHECK_NE(Fraction{2, 5} * 5.0 / Fraction{1, 3} * 0.6, Fraction{2, 5});

        CHECK_EQ(Fraction{-1, 3} * 3.0 + Fraction{-1, 2}, Fraction{-3, 2});
        CHECK_EQ(Fraction{-2, 3} * 1.5 - Fraction{-1, 4}, Fraction{-3, 4});

        CHECK_EQ(0.5 * Fraction{-3, 4} + Fraction{-1, 4} * 2.0, Fraction{-7, 8});
        CHECK_EQ((Fraction{-2, 5} * 5.0) / (Fraction{-1, 3} * 0.6), Fraction{10, 1});
    }

    TEST_CASE("Distributivity of multiplication over addition and subtraction with floating-point numbers") {
        CHECK_EQ(2.0 * (Fraction{1, 4} + Fraction{1, 2}), 2.0 * Fraction{1, 4} + 2.0 * Fraction{1, 2});
        CHECK_NE(2.0 * (Fraction{1, 4} + Fraction{1, 2}), 2.0 * Fraction{1, 4} + 3.0 * Fraction{1, 2});
        CHECK_EQ(2.0 * (Fraction{-1, 4} + Fraction{-1, 2}), 2.0 * Fraction{-1, 4} + 2.0 * Fraction{-1, 2});

        CHECK_EQ(2.0 * (Fraction{1, 4} - Fraction{1, 2}), 2.0 * Fraction{1, 4} - 2.0 * Fraction{1, 2});
        CHECK_NE(2.0 * (Fraction{1, 4} - Fraction{1, 2}), 2.0 * Fraction{1, 4} - 3.0 * Fraction{1, 2});
        CHECK_EQ(2.0 * (Fraction{-1, 4} - Fraction{-1, 2}), 2.0 * Fraction{-1, 4} - 2.0 * Fraction{-1, 2});
    }
}

TEST_SUITE("Pre and post increment and decrement") {
    TEST_CASE("Pre increment") {
        Fraction frac{1, 2};
        Fraction control{3, 2};
        CHECK_EQ(++frac, control);
        CHECK_NE(++frac, control);

        // Result changes signs
        Fraction neg_frac{-1, 2};
        Fraction neg_control{1, 2};
        CHECK_EQ(++neg_frac, neg_control);
        CHECK_NE(++neg_frac, neg_control);
    }

    TEST_CASE("Post increment") {
        Fraction frac{2, 7};
        Fraction control{9, 7};
        CHECK_NE(frac++, control);
        CHECK_EQ(frac++, control);

        // Result changes signs
        Fraction neg_frac{-2, 7};
        Fraction neg_control{5, 7};
        CHECK_NE(neg_frac++, neg_control);
        CHECK_EQ(neg_frac++, neg_control);
    }

    TEST_CASE("Pre decrement") {
        Fraction frac{3, 2};
        Fraction control{1, 2};
        CHECK_EQ(--frac, control);
        CHECK_NE(--frac, control);

        // Result changes signs
        Fraction neg_frac{1, 2};
        Fraction neg_control{-1, 2};
        CHECK_EQ(--neg_frac, neg_control);
        CHECK_NE(--neg_frac, neg_control);
    }

    TEST_CASE("Post decrement") {

        Fraction frac{9, 7};
        Fraction control{2, 7};
        CHECK_NE(frac--, control);
        CHECK_EQ(frac--, control);

        // Result changes signs
        Fraction neg_frac{2, 7};
        Fraction neg_control{-5, 7};
        CHECK_NE(neg_frac--, neg_control);
        CHECK_EQ(neg_frac--, neg_control);
    }

    TEST_CASE("Chained increment and decrement with an operation") {
        Fraction frac1{1, 2};
        Fraction frac2{2, 3};
        Fraction control{5, 6};
        CHECK_EQ(frac1-- * frac2, Fraction{1,3 });
        CHECK_EQ(--frac1 + frac2, Fraction{-5,6 });
        CHECK_EQ(frac1++ - frac2, Fraction{-13,6 });
        CHECK_EQ(++frac1 / frac2, Fraction{3,4 });

    }

    TEST_CASE("Chained increment and decrement with comparisons") {
        Fraction frac11{1, 2};
        Fraction frac22{2, 3};
        Fraction frac33{3, 2};
        Fraction frac44{4, 3};

        // Post-increment and pre-increment
        bool result1 = (frac11++ < frac22) && (++frac33 > frac44);
        CHECK(result1);

        // Post-decrement and pre-decrement
        result1 = (frac11-- < frac22) && (--frac33 > frac44);
    }
}

TEST_SUITE("Input and output operators tests") {
    TEST_CASE("Output stream operator (<<)") {
        std::stringstream ss;

        // Numerator and denominator are positive
        Fraction frac{3, 4};
        ss << frac;
        CHECK(ss.str() == "3/4");

        // Numerator is negative and denominator is positive
        ss.str("");
        Fraction neg_frac{-7, 9};
        ss << neg_frac;
        CHECK(ss.str() == "-7/9");

        // Numerator is positive and denominator is negative
        ss.str("");
        Fraction neg_frac2{3, -4};
        ss << neg_frac2;
        CHECK(ss.str() == "-3/4");

        // Expanded fraction, both positive
        ss.str("");
        Fraction expanded{30, 60};
        ss << expanded;
        CHECK(ss.str() == "1/2");

        //Expanded fraction, numerator is negative
        ss.str("");
        Fraction expanded_neg{-36, 40};
        ss << expanded_neg;
        CHECK(ss.str() == "-9/10");

        //Expanded fraction, both are negative
        ss.str("");
        Fraction expanded_both_neg{-64, -72};
        ss << expanded_both_neg;
        CHECK(ss.str() == "8/9");

    }

    TEST_CASE("Input stream operator (>>)") {
        std::stringstream ss("5 8");
        Fraction frac;
        ss >> frac;
        CHECK_EQ(frac, Fraction{5, 8});

        ss.clear();
        ss.str("-11 13");
        Fraction neg_frac;
        ss >> neg_frac;
        CHECK_EQ(neg_frac, Fraction{-11, 13});
    }

    TEST_CASE("Chaining input and output operators") {
        std::stringstream ss_in("1 2 3 -4");
        Fraction frac1, frac2;
        ss_in >> frac1 >> frac2;
        CHECK_EQ(frac1, Fraction{1, 2});
        CHECK_EQ(frac2, Fraction{3, -4});

        std::stringstream ss_out;
        ss_out << frac1 << " and " << frac2;
        CHECK(ss_out.str() == "1/2 and -3/4");
    }

    TEST_CASE(">> operator with zero denominator") {
        std::stringstream ss_zero_denominator("3 0");

        Fraction frac1;
        CHECK_THROWS_AS(ss_zero_denominator >> frac1, std::runtime_error);

        ss_zero_denominator.str("6 8 3 0");
        Fraction frac2, frac3;
        CHECK_THROWS_AS(ss_zero_denominator >> frac2 >> frac3, std::runtime_error);
    }

    TEST_CASE(">> operator with zero numerator") {
        std::stringstream ss_valid_denominator("0 4");

        Fraction frac;
        CHECK_NOTHROW(ss_valid_denominator >> frac);
        CHECK_EQ(frac, Fraction{0, -8});
    }

    TEST_CASE(">> Operator with floating-point input") {
        std::stringstream ss_floating_point("3.556 4");

        Fraction frac;
        CHECK_THROWS_AS(ss_floating_point >> frac, std::runtime_error);
    }
}

TEST_CASE("Fraction with largest possible numerator and/or denominator and overflow handling") {
    int max_int = std::numeric_limits<int>::max();
    int min_int = std::numeric_limits<int>::min();

    // Test largest possible numerator
    CHECK_NOTHROW(Fraction f1(max_int, 1));
    Fraction f1(max_int, 1);
    CHECK_EQ(f1, Fraction(max_int, 1));

    // Test largest possible denominator
    CHECK_NOTHROW(Fraction f2(1, max_int));
    Fraction f2(1, max_int);
    CHECK_EQ(f2, Fraction(1, max_int));

    // Test largest possible numerator and denominator
    CHECK_NOTHROW(Fraction f3(max_int, max_int));
    Fraction f3(max_int, max_int);
    CHECK_EQ(f3, Fraction(1, 1));

    // Test arithmetic with large numerator and/or denominator
    Fraction f4(max_int - 100, max_int);

    CHECK_THROWS_AS(f1 * f4, std::overflow_error);
    CHECK_THROWS_AS(f1 / f4, std::overflow_error);

    CHECK_THROWS_AS(f2 * f4, std::overflow_error);
    CHECK_THROWS_AS(f2 / f4, std::overflow_error); //

    CHECK_NOTHROW(f3 * f4);
    CHECK_NOTHROW(f4 / f3);

    Fraction f5(max_int - 1, 1);
    Fraction f6(min_int, 1);
    Fraction f7(min_int + 1, 1);

    CHECK_THROWS_AS(f1 + f5, std::overflow_error);
    CHECK_THROWS_AS(f6 + f7, std::overflow_error);

    CHECK_THROWS_AS(f1 - f6, std::overflow_error);
    CHECK_THROWS_AS(f5 - f7, std::overflow_error);

    CHECK_NOTHROW(f5 + Fraction{1, 1});
    CHECK_NOTHROW(f7 - Fraction{1, 1});
}