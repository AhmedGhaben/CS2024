#include <iostream>
#include <cmath>


class Fraction {
private:
// fields
    int nu;
    int de;

// simplify the fraction
void simp(){
    if (de == 0) {
        throw "Denominator cannot be 0!";;
    } else {
        int res = std::min(nu, de);

        while (res > 1) {
            if (nu % res == 0 && de % res == 0) {
                nu /= res;
                de /= res;
                break;
            }
            res--;
        }

        if (de < 0) {
            de *= -1;
            nu *= -1;
        }
    }
}

public:

// constructors and destructors
~Fraction() = default;
Fraction(const int n = 0, const int d = 1){
    if(d == 0){
        throw "Denominator cannot be 0!";
    }
    else{
        nu = n;
        de = d;
    simp();
    }
}
// getters
int getNumerator() const { 
    return nu; 
}
int getDenominator() const {
    return de;
    }

// setters
void setNumerator(int numerator){
    nu = numerator;
    simp();
}
void setDenominator(int denominator){
    if(denominator != 0){ 
    de = denominator;
    simp();
    }
    else if (denominator == 0){
        throw "Denominator cannot be 0!";;
    }
}

// converge from fraction to double
double conv(){
    double cnvg = 0;
    cnvg = static_cast<double>(nu)/de;
    return cnvg;
}





// overloaded compound assignments
// sum
Fraction& operator+=(const Fraction& other){
    
    nu = (nu*other.de + other.nu*de);
    de *= other.de;
    simp();
    return *this;
}

// minus
Fraction& operator-=(const Fraction& other){

    nu = (nu*other.de - other.nu*de);  
    de *= other.de;
    simp();
    return *this;
}
// times
Fraction operator*=(const Fraction& other){
    nu *= other.nu;
    de *= other.de;
    simp();
    return *this;
    }

//  division
Fraction& operator/=(const Fraction& other){
    if (other.nu != 0){
    nu *= other.de;
    de *= other.nu;
    simp();
}
    else {
        throw "Denominator cannot be 0!";;
    }
    return *this;
}
Fraction& operator=(const Fraction& other){
    nu = other.nu;
    de = other.de;
    simp();
    return *this;
}

// arithmatic operators(static)
// sum

friend Fraction operator+(const Fraction& a,const Fraction& b){
    int new_de, new_nu;

    new_nu = (a.nu*b.de + b.nu*a.de);
    new_de = a.de * b.de;
    Fraction result(new_nu, new_de);
    result.simp();
    return result;
}
// minus
friend Fraction operator-(const Fraction& a, const Fraction& b){
    int new_de, new_nu;

    new_nu = (a.nu*b.de - b.nu*a.de);  
    new_de = a.de*b.de;
    Fraction result(new_nu, new_de);
    result.simp();
    return result;
}
// times
friend Fraction operator*(const Fraction& a, const Fraction& b){
    int new_nu, new_de;
    new_nu = a.nu*b.nu;
    new_de = a.de * b.de;
    Fraction result(new_nu, new_de);
    result.simp();
    return result;}
//  division
friend Fraction operator/(const Fraction& a, const Fraction& b){
    if (b.nu != 0){
        int new_nu, new_de;
        new_nu = a.nu * b.de;
        new_de = b.nu * a.de;
        Fraction result(new_nu, new_de);
        result.simp();
        return result;
    }
    else {
        throw "Denominator cannot be 0!";;
    }
}

// << operator
friend std::ostream& operator<<(std::ostream& os, const Fraction& f){
    if (f.de == 0){
        throw "Denominator cannot be 0!";;
    }
    else{
    os << f.nu << '/' << f.de;
}
    return os;
}
// >> operator
friend std::istream& operator>>(std::istream& is, Fraction& f){
    char slash;
    is >> f.nu >> slash >> f.de;
    if (f.de == 0){
        is.setstate(std::ios::failbit);
        throw "Denominator cannot be 0!";}
    else{
        f.simp();
    }
        return is;
    
}

// << >> operators
friend std::istream& operator >>(std::istream& is, Vector& vctr){
    
}
};


int main() {

try{
    // Create fractions
    Fraction f1;
    std::cout << "Enter the first fraction in the form (a/b): ";
    std::cin >> f1;

    Fraction f2;
    std::cout << "Enter the second fraction in the form (a/b): ";
    std::cin >> f2;

    std::cout << "First fraction: " << f1 << "Second fraction" << f2 << std::endl;

    // Test arithmetic operators
    std::cout << "f1 + f2: " << (f1 + f2) << std::endl;
    std::cout << "f1 - f2: " << (f1 - f2) << std::endl;
    std::cout << "f1 * f2: " << (f1 * f2) << std::endl;
    std::cout << "f1 / f2: " << (f1 / f2) << std::endl;

    // Test overloaded compound opeerators
    f1 += f2;
    std::cout << "f1 += f2: " << f1 << std::endl;

    f1 -= f2;
    std::cout << "f1 -= f2: " << f1 << std::endl;

    f1 *= f2;
    std::cout << "f1 *= f2: " << f1 << std::endl;

    f1 /= f2;
    std::cout << "f1 /= f2: " << f1 << std::endl;

    // Test converting to double
    Fraction f3;
    std::cout << "Enter a fraction to convert into a double: ";
    std::cin >> f3;
    std::cout << "The fraction equals: " << f3.conv() << std::endl;

    // Testing getters and setters
    int n1 = 0, n2 = 0;
    std::cout << "Set new numerator to the second fraction: " << std::endl;
    std::cin >> n1;
    f2.setNumerator(n1);
    std::cout << "The new numerator equals; " << f2.getNumerator() << std::endl;
    std::cout << "Set new denominator to the second fraction: " << std::endl;
    std::cin >> n2;
    f2.setDenominator(n2);
    std::cout << "The new denominator equals; " << f2.getDenominator() << std::endl;
}
catch(const char* txtExeption){
    std::cout << txtExeption << std::endl;
}
    return 0;
}