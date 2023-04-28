#include "Fraction.hpp"
#include <stdexcept>
#include <sstream>
using namespace std;
namespace ariel {

        Fraction::Fraction(int numerator, int denominator){
            if(denominator==0){
                throw invalid_argument("Denominator cant be 0 ");
            }
            this->denominator=denominator;
            this->numerator=numerator;
            simplify();
        }
/*
        Fraction::Fraction(const Fraction& other){
            this->denominator=other.getDenominator();
            this->numerator=other.getNumerator(); 
            simplify(); 
        }
 */       
        Fraction::Fraction(){
            this->denominator=1;
            this->numerator=0;
        }
        /*
        Fraction& Fraction::operator=(const Fraction &other){
            if(this != &other)
            {
                numerator=other.numerator;
                denominator=other.denominator;
            }
            return *this;
            
        }
*/
        std::string Fraction::to_string()const{
            std::stringstream ss;
            ss << numerator << "/" << denominator;
            return ss.str();
        }

        Fraction& Fraction::operator++() {
            numerator += denominator;
            simplify();
            return *this;
        }

        Fraction& Fraction::operator--() {
        numerator -= denominator;
        simplify();
        return *this;
        }
        Fraction Fraction::operator++(int) {
            Fraction temp(*this);
            numerator += denominator;
            simplify();
            return temp;
        } 
        
        Fraction Fraction::operator--(int) {
            Fraction temp(*this);
            numerator -= denominator;
            simplify();
            return temp;
        } 
        void Fraction::simplify() {
            int gcd = std::__gcd(numerator, denominator);
            numerator /= gcd;
            denominator /= gcd;
        }       
}
    
