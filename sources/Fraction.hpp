#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

namespace ariel {

    class Fraction {

    public:
        // Constructors
        Fraction(int numerator,int denominator);
        // coversion constructor 
        Fraction(int num):numerator(num),denominator(1){}
        // defult constructor
        Fraction();
        // Copy constructor
       // Fraction(const Fraction& other);

        
        // Helper method to simplify the fraction
        void simplify();

        //Fraction& operator=(const Fraction &other);

        //Arithmetic

        friend Fraction operator+(const Fraction & fraction1, const Fraction &fraction2){
            int Nnew = fraction1.numerator * fraction2.denominator + fraction2.numerator * fraction1.denominator;
            int Dnew= fraction2.denominator * fraction1.denominator;
            Fraction res (Nnew,Dnew);
           res.simplify();
            return res;
        }
        // int +
        friend Fraction operator+(const int& NUM, const Fraction& fraction) {
            int new_numerator = NUM * fraction.denominator + fraction.numerator;
            Fraction res (new_numerator, fraction.denominator);
            res.simplify();
            return res;
        }
        // float +
        
        friend Fraction operator+(const float& NUM, const Fraction& frac) {
            int new_numerator = static_cast<int>(NUM)* frac.denominator + frac.numerator;
            Fraction res (new_numerator, frac.denominator);
            res.simplify();
            return res;
        }
        //+ float
        
        friend Fraction operator+( const Fraction& frac,const float& NUM) {
            int new_numerator = static_cast<int>(NUM)* frac.denominator + frac.numerator;
            Fraction res (new_numerator, frac.denominator);
            res.simplify();
            return res;
        }     

        friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2){
            int Nnew = fraction1.numerator * fraction2.denominator - fraction2.numerator * fraction1.denominator;
            int Dnew = fraction2.denominator * fraction1.denominator;
            Fraction res (Nnew,Dnew);
            res.simplify();
            return res;
        }

        friend Fraction operator-( const Fraction& frac,const float& NUM) {
            int new_numerator = static_cast<int>(NUM )* frac.denominator - frac.numerator;
            Fraction res (new_numerator, frac.denominator);
            res.simplify();
            return res;
        }
       
        friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2){
            int Nnew = fraction1.numerator *  fraction2.numerator ;
            int Dnew = fraction2.denominator * fraction1.denominator;
            Fraction res (Nnew,Dnew);
            res.simplify();
            return res;
        }
        friend Fraction operator*(const float & NUM, const Fraction& fraction) {
            int Nnew=static_cast<int>(NUM) * fraction.numerator;
            Fraction res (Nnew, fraction.denominator);
            res.simplify();
            return res;
        }
        friend Fraction operator/(const Fraction& fraction1, const Fraction& fraction2){
            int Nnew = fraction1.numerator *  fraction2.denominator ;
            int Dnew = fraction1.denominator * fraction2.numerator;
            Fraction res (Nnew,Dnew);
            res.simplify();
            return res;
        }
        // Comparison operators
        friend bool operator==(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1.numerator * fraction2.denominator == fraction2.numerator * fraction1.denominator);
        }
        friend bool operator!=(const Fraction& fraction1, const Fraction& fraction2){
            return !(fraction1==fraction2);
        }
        friend bool operator>(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator);
        }
        
        friend bool operator>(const Fraction& fraction, const float value) {
            float fractionValue = static_cast<float>(fraction.numerator) / static_cast<float>(fraction.denominator);
            return fractionValue > value;
        }
        friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1>fraction2 || fraction1==fraction2);
        }
        friend bool operator<(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator);
        }
        friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1==fraction2 || fraction1<fraction2);
        }

        //increment and decrement
        Fraction & operator++();
        Fraction  operator++(int);
        Fraction & operator--();
        Fraction  operator--(int);

        //output 
        friend std::ostream& operator<<(std::ostream& ostream, const Fraction& fraction){
            ostream << fraction.numerator << "/" << fraction.denominator;
            return ostream;

        }

        int getNumerator() const { return numerator; }
        int getDenominator() const { return denominator; }
        // toString method
        std::string to_string()const;

        private:
        int numerator;
        int denominator;

    
    };
}
#endif