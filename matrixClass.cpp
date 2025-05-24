#include <iostream>
#include <string>
#include <vector>
#include <memory>

template<size_t Rows, size_t Cols>
class Matrix {
private:
    std::unique_ptr<std::vector<std::vector<double>>> data;

public:
    Matrix() : data(std::make_unique<std::vector<std::vector<double>>>(Rows, std::vector<double>(Cols, 0.0))) {}
    
    Matrix(const std::initializer_list<std::initializer_list<double>>& elems) 
        : data(std::make_unique<std::vector<std::vector<double>>>()) {
        if (elems.size() != Rows) {
            throw std::string("Invalid number of rows in initializer list");
        }
        for (const auto& row : elems) {
            if (row.size() != Cols) {
                throw std::string("Invalid number of columns in initializer list");
            }
            data->emplace_back(row);
        }
    }
    
    ~Matrix() = default;
    
    Matrix(const Matrix& other) 
        : data(std::make_unique<std::vector<std::vector<double>>>(*other.data)) {}
    
    Matrix(Matrix&& other) noexcept : data(std::move(other.data)) {}
    
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            data = std::make_unique<std::vector<std::vector<double>>>(*other.data);
        }
        return *this;
    }
    
    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }
    
    size_t rows() const { return Rows; }
    size_t cols() const { return Cols; }
    
    double get(size_t row, size_t col) const {
        if (row >= Rows || col >= Cols) {
            throw std::string("Matrix index out of range");
        }
        return (*data)[row][col];
    }
    
    void set(size_t row, size_t col, double value) {
        if (row >= Rows || col >= Cols) {
            throw std::string("Matrix index out of range");
        }
        (*data)[row][col] = value;
    }
    
    template<size_t OtherCols>
    Matrix<Rows, OtherCols> operator*(const Matrix<Cols, OtherCols>& other) const {
        Matrix<Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < OtherCols; ++j) {
                double sum = 0.0;
                for (size_t k = 0; k < Cols; ++k) {
                    sum += (*data)[i][k] * other.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        return result;
    }
    
    Matrix<Rows, Cols> operator+(const Matrix<Rows, Cols>& other) const {
        Matrix<Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.set(i, j, (*data)[i][j] + other.get(i, j));
            }
        }
        return result;
    }
    
    Matrix<Rows, Cols> operator-(const Matrix<Rows, Cols>& other) const {
        Matrix<Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.set(i, j, (*data)[i][j] - other.get(i, j));
            }
        }
        return result;
    }
    
    Matrix<Rows, Cols>& operator+=(const Matrix<Rows, Cols>& other) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                (*data)[i][j] += other.get(i, j);
            }
        }
        return *this;
    }
    
    Matrix<Rows, Cols>& operator-=(const Matrix<Rows, Cols>& other) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                (*data)[i][j] -= other.get(i, j);
            }
        }
        return *this;
    }
    
    Matrix<Rows, Cols> operator*(double scalar) const {
        Matrix<Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result.set(i, j, (*data)[i][j] * scalar);
            }
        }
        return result;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
        os << "Matrix " << Rows << "x" << Cols << ":\n";
        for (size_t i = 0; i < Rows; ++i) {
            os << "[ ";
            for (size_t j = 0; j < Cols; ++j) {
                os << mat.get(i, j) << " ";
            }
            os << "]\n";
        }
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Matrix& mat) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                double value;
                is >> value;
                mat.set(i, j, value);
            }
        }
        return is;
    }
};

template<size_t Rows, size_t Cols>
auto transpose(Matrix<Rows, Cols>&& mat) {
    Matrix<Cols, Rows> result;
    for (size_t i = 0; i < Rows; ++i) {
        for (size_t j = 0; j < Cols; ++j) {
            result.set(j, i, mat.get(i, j));
        }
    }
    return result;
}

auto trace = [](const auto& mat) {
    if (mat.rows() != mat.cols()) {
        throw std::string("Trace is only defined for square matrices");
    }
    double sum = 0.0;
    for (size_t i = 0; i < mat.rows(); ++i) {
        sum += mat.get(i, i);
    }
    return sum;
};

int main() {
    try {
        Matrix<2, 3> m1 = {
        {1, 2, 3},
        {4, 5, 6}
        };
    
        Matrix<3, 2> m2 = {
        {7, 8},
        {9, 10},
        {11, 12}
        };
    
        std::cout << "\nMatrix m1:\n" << m1;
        std::cout << "Matrix m2:\n" << m2;
        
        auto m3 = m1 * m2;
        std::cout << "Matrix multiplication (m1 * m2):\n" << m3;
        
        auto transposed = transpose(std::move(m1));
        std::cout << "Transposed m1:\n" << transposed;
        
        Matrix<2, 2> square = {
            {1, 2},
            {3, 4}
        };
        std::cout << "Square matrix:\n" << square;
        std::cout << "Trace of square matrix: " << trace(square) << std::endl;
        
        Matrix<2, 3> m4 = {{1, 2, 3}, {4, 5, 6}};
        std::cout << "Trace: " << trace(m4) << std::endl;
    } catch (const std::string& s) {
        std::cout << "Error: " << s << std::endl;
    }

    return 0;
}