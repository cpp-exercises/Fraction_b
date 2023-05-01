#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <cmath>
using namespace std;
namespace ariel {

    class Fraction {

    public:
        static constexpr double ROUNDED = 1000;

        // Constructors
        Fraction(int numerator,int denominator);
        // coversion constructor 
        Fraction(int num):numerator(num),denominator(1){}
        Fraction(double num):numerator(static_cast<int>(num*ROUNDED)),denominator(static_cast<int>(ROUNDED)){}
        Fraction(float num):numerator(static_cast<int>(num*ROUNDED)),denominator(static_cast<int>(ROUNDED)){}

        // defult constructor

        Fraction();
        // Copy constructor
       // Fraction(const Fraction& other);

        
        // Helper method to simplify the fraction
        void simplify();
        void ThrowsException();
        //Fraction& operator=(const Fraction &other);

        //Arithmetic

      friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2) {
        int64_t numerator = static_cast<int64_t>(fraction1.numerator) * fraction2.denominator + 
                            static_cast<int64_t>(fraction2.numerator) * fraction1.denominator;
        int64_t denominator = static_cast<int64_t>(fraction1.denominator) * fraction2.denominator;

        if (numerator > std::numeric_limits<int>::max() || numerator < std::numeric_limits<int>::min() || 
            denominator > std::numeric_limits<int>::max() || denominator < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow during addition");
        }

        Fraction result(static_cast<int>(numerator), static_cast<int>(denominator));
        result.simplify();
        return result;
    }
        // int +
        friend Fraction operator+(const int& NUM, const Fraction& fraction) {
            double new_numerator = NUM * fraction.denominator + fraction.numerator;
            Fraction res (static_cast<int>(new_numerator), fraction.denominator);
            res.simplify();
            return res;
        }
        
        //+ double
        
        friend Fraction operator+( const Fraction& frac,const double& NUM) {

            Fraction frac2(NUM);
            double new_denominator = frac.denominator*ROUNDED;
            double new_numerator= frac.numerator*ROUNDED;
            double decimal_v = new_numerator/new_denominator;
            double rounded = round(decimal_v*ROUNDED)/ROUNDED;
            Fraction res1 (rounded);
            Fraction res=res1+frac2;
            res.simplify();
            return res;
        }  
        // double +
        friend Fraction operator+(const double& NUM, const Fraction& frac) {
            Fraction res = frac+NUM;
            res.simplify();
            return res;
        }

       friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2) {
        if (fraction1.denominator == 0 || fraction2.denominator == 0) {
            throw std::invalid_argument("Division by zero error!");
        }
        long long int num = static_cast<long long int>(fraction1.numerator) * fraction2.denominator
                            - static_cast<long long int>(fraction2.numerator) * fraction1.denominator;
        long long int den = static_cast<long long int>(fraction1.denominator) * fraction2.denominator;

        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() 
            || den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow during subtraction!");
        }

        Fraction res(static_cast<int>(num), static_cast<int>(den));
        res.simplify();
        return res;
    }

        friend Fraction operator-(const Fraction& frac,const double& NUM) {
            Fraction frac2(NUM);
            double new_denominator = frac.denominator*ROUNDED;
            double new_numerator = frac.numerator*ROUNDED;
            double decimal_v = new_numerator/new_denominator;
            double rounded = round(decimal_v*ROUNDED)/ROUNDED;
            Fraction res1 (rounded);
            Fraction res =res1-frac2;
            res.simplify();
            return res;
        }
        friend Fraction operator-(const double& NUM,const Fraction& frac)
        {
            Fraction frac2(NUM);
            double new_denominator = frac.denominator*ROUNDED;
            double new_numerator = frac.numerator*ROUNDED;
            double decimal_v = new_numerator/new_denominator;
            double rounded = round(decimal_v*ROUNDED)/ROUNDED;
            Fraction res1 (rounded);
            Fraction res =frac2-res1;
            res.simplify();
            return res;
            
        }
        
      friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2){
        long long  num = static_cast<long long >(fraction1.numerator) * fraction2.numerator;
        long long  den = static_cast<long long >(fraction1.denominator) * fraction2.denominator;

        // Check for overflow
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() ||
            den > std::numeric_limits<int>::max() || den < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow during multiplication");
        }
        Fraction res(static_cast<int>(num), static_cast<int>(den));
        res.simplify();
        return res;
    }


        friend Fraction operator*(const double & NUM, const Fraction& fraction) {
            double Nnew=NUM;
            Fraction frac2(Nnew);
            Fraction res =frac2*fraction;
            res.simplify();
            return res;
        }
         friend Fraction operator*( const Fraction& fraction,const double & NUM) {
            Fraction frac (NUM);
            Fraction res =fraction*frac;
            res.simplify();
            return res;
        }
        friend Fraction operator/(const Fraction& fraction1, const Fraction& fraction2){
            int max_int = numeric_limits<int>::max();
            if(fraction2.numerator==0){
                throw std::runtime_error(" can't divide by zero ");
            }
            if ((fraction1.numerator != 0 && fraction2.denominator != 0) && (fraction1.numerator == max_int || fraction2.denominator == max_int)) {
                throw std::overflow_error("Overflow during multiplication");
            }
            int Nnew = fraction1.numerator *  fraction2.denominator ;
            int Dnew = fraction1.denominator * fraction2.numerator;
            Fraction res (Nnew,Dnew);
            res.simplify();
            return res;
        }

          friend Fraction operator/(const Fraction& fraction1, const double& NUM){
            if(NUM==0){
                throw std::runtime_error(" cant  numerator/0 ");
            }
            Fraction frac2(NUM);
            Fraction res =fraction1/frac2;
            res.simplify();
            return res;
        }
          friend Fraction operator/( const float& NUM,const Fraction& fraction1){
            
            Fraction frac2(NUM);
            Fraction res =frac2/fraction1;
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
           bool res = fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator;
           if(fraction1.denominator < 0 && fraction2.denominator > 0){
             return !res;
           }
            if(fraction2.denominator < 0 && fraction1.denominator > 0){
            return !res;
           }
           return res;
        }
        
        friend bool operator>(const Fraction& fraction, const float value) {
            float fractionValue = static_cast<float>(fraction.numerator) / static_cast<float>(fraction.denominator);
            return fractionValue > value;
        }
        friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2){
            return (fraction1>fraction2 || fraction1==fraction2);
        }
        friend bool operator<(const Fraction& fraction1, const Fraction& fraction2){
            
            return !(fraction1 > fraction2) &&  fraction1!=fraction2;
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
        friend   std::ostream& operator<<(std::ostream& osin, const Fraction& frac) {
            if (frac.denominator < 0) {
                osin << "-" << std::abs(frac.numerator) << "/" << std::abs(frac.denominator);
            } else {
                osin << frac.numerator << "/" << frac.denominator;
            }
            return osin;
        }
        friend std::istream& operator>>(std::istream& inst, Fraction& frac) {
        int numerator=0;
        int denominator=1;
        if (!(inst >> numerator)) {
            throw std::runtime_error("Invalid input format for Fraction numerator");
        }
        
        if (!(inst >> denominator)) {
            throw std::runtime_error("Invalid input format for Fraction denominator");
        }
        if(denominator==0){
            throw std::runtime_error("a/0");
        }
        frac = Fraction(numerator, denominator);
        return inst;
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