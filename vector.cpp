#include <iostream>
#include <cmath>
#include <vector>

class Vector{
    private:
    // fields
    std::vector<double> vector;

    public:
    // coonstructors and destructors
    ~Vector() = default;
    Vector() = default;
    Vector(int size) : vector(size, 0.0) {}
    Vector(const Vector& other) : vector(other.vector) {}
    Vector(const std::initializer_list<double>& elems) : vector(elems) {}

    // getters and setters

    int get_size() const {return vector.size();}

    double get(int index) const {
        if (index >= vector.size()) {throw "Index is out of range";}
        return vector[index];
    }

    void set(int index, double coordinate) {
        if (index >= vector.size()) {throw "index out of range";}
        vector[index] = coordinate;
    }

    // overloaded compound assignments

    Vector& operator=(const Vector& other){
        vector = other.vector;
    return *this;
    }
    
    Vector & operator+=(const Vector & other){
        if (vector.size() != other.vector.size()) {
            throw "Vectors must be of the same name";
        }
        for(int i = 0; i < vector.size(); i++){
        vector[i]+= other.vector[i];
        }
        return *this;
    }

    Vector & operator-=(const Vector & other){
        if (vector.size() != other.vector.size()) {
            throw "Vectors must be of the same name";
        }
        for(int i = 0; i < vector.size(); i++){
            vector[i]-= other.vector[i];
        }
        return *this;
    }
    
    double operator*(const Vector & other){
        double scalar = 0.0;
        
        if (vector.size() != other.vector.size()) {
            throw "Vectors must be of the same name";
        }
        
        for(int i = 0; i < vector.size(); i++){
        scalar += vector[i] * other.vector[i];
        }
        return scalar;
    }

    Vector operator*(const double scalar) {
        Vector result = *this;
        for(double& element : result.vector){
            element *= scalar;
        }
        return result;
    }

    // arithmetic operators

    Vector operator+(const Vector& other) const{
        Vector result = *this;
        result += other;
        return result;
    }

    Vector operator-(const Vector& other) const{
        Vector result = *this;
        result -= other;
        return result;
    }


// << >> operators
friend std::istream& operator >>(std::istream& is, Vector& vctr){
    int size;
    for(double& elm : vctr.vector){
        is >> elm;
}
return is;
}

friend std::ostream& operator<<(std::ostream& os, const Vector& vctr) {
    os << '[';
    for (size_t i = 0; i < vctr.vector.size(); ++i) {
        os << vctr.vector[i];
        if (i != vctr.vector.size() - 1) {
            os << ", ";
        }
    }
    os << ']';
    return os;
}
};

    int main() {

    Vector v1(3);
    Vector v2(3);

    std::cout << "Enter vector v1 (" << '3' << " elements): ";
    std::cin >> v1;
    std::cout << "Enter vector v2 (" << '3' << " elements): ";
    std::cin >> v2;

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    Vector sum = v1 + v2;
    std::cout << "Sum: " << sum << std::endl;

    Vector difference = v1 - v2;
    std::cout << "Difference: " << difference << std::endl;

    double dotProduct = v1 * v2;
    std::cout << "Dot Product: " << dotProduct << std::endl;

    v2 += v1;
    std::cout << "v2 += v1 is: " << v2 << std::endl;
    double scalar;
    std::cout << "A scalar to multiply v1 by: ";
    std::cin >> scalar;
    Vector scaled = v1 * scalar;
    std::cout << "Scaled: " << scaled << std::endl;


    return 0;
    }
