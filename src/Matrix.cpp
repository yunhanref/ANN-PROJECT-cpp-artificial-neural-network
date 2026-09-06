#include "Matrix.h"
#include <cstdlib>
#include <ctime>
#include <stdexcept>


Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data = new double[r * c]();
}


Matrix::~Matrix() noexcept {
    delete[] data;
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new double[rows * cols];
    for (int i = 0; i < rows * cols; i++) {
        data[i] = other.data[i];
    }
}


Matrix::Matrix(Matrix&& other) noexcept : rows(other.rows), cols(other.cols), data(other.data) {
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    double* new_data = new double[other.rows * other.cols];
    for (int i = 0; i < other.rows * other.cols; i++) {
        new_data[i] = other.data[i];
    }
    delete[] data;
    rows = other.rows;
    cols = other.cols;
    data = new_data;
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this == &other) return *this;
    delete[] data;
    rows = other.rows;
    cols = other.cols;
    data = other.data;
    other.rows = 0;
    other.cols = 0;
    other.data = nullptr;
    return *this;
}


double& Matrix::at(int r, int c) {
    return data[r * cols + c];
}

const double& Matrix::at(int r, int c) const {
    return data[r * cols + c];
}

double& Matrix::operator()(int r, int c) {
    return data[r * cols + c];
}

const double& Matrix::operator()(int r, int c) const {
    return data[r * cols + c];
}


Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) throw DimensionMismatchException();
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            double sum = 0;
            for (int k = 0; k < cols; ++k) {
                sum += at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    
    if (rows == other.rows && other.cols == 1) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            double val = other.at(i, 0);
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = at(i, j) + val;
            }
        }
        return result;
    }
    
    if (cols == other.cols && other.rows == 1) {
        Matrix result(rows, cols);
        for (int j = 0; j < cols; ++j) {
            double val = other.at(0, j);
            for (int i = 0; i < rows; ++i) {
                result.at(i, j) = at(i, j) + val;
            }
        }
        return result;
    }

    if (rows != other.rows || cols != other.cols) throw DimensionMismatchException();
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}


Matrix Matrix::operator-(const Matrix& other) const {

    if (rows == other.rows && other.cols == 1) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            double val = other.at(i, 0);
            for (int j = 0; j < cols; ++j) {
                result.at(i, j) = at(i, j) - val;
            }
        }
        return result;
    }
    
    if (cols == other.cols && other.rows == 1) {
        Matrix result(rows, cols);
        for (int j = 0; j < cols; ++j) {
            double val = other.at(0, j);
            for (int i = 0; i < rows; ++i) {
                result.at(i, j) = at(i, j) - val;
            }
        }
        return result;
    }
    if (rows != other.rows || cols != other.cols) throw DimensionMismatchException();
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}


Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

Matrix Matrix::operator+(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] + scalar;
    }
    return result;
}

Matrix Matrix::operator-(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] - scalar;
    }
    return result;
}

Matrix Matrix::operator/(double scalar) const {
    if (scalar == 0.0) throw std::runtime_error("[Hata]: Sifira bolme hatasi.");
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] / scalar;
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

Matrix operator+(double scalar, const Matrix& matrix) {
    return matrix + scalar;
}


Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < rows * cols; i++) {
        data[i] *= scalar;
    }
    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    if (scalar == 0.0) throw std::runtime_error("[Hata]: Sifira bolme hatasi.");
    for (int i = 0; i < rows * cols; i++) {
        data[i] /= scalar;
    }
    return *this;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at(j, i) = at(i, j);
        }
    }
    return result;
}

Matrix Matrix::hadamard(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) throw DimensionMismatchException();
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}

void Matrix::randomize(double minVal, double maxVal) {
    for (int i = 0; i < rows * cols; i++) {
        data[i] = minVal + ((double)std::rand() / RAND_MAX) * (maxVal - minVal);
    }
}


void Matrix::print() const {
    std::cout << *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.at(i, j);
            if (j < matrix.cols - 1) os << "\t";
        }
        os << "\n";
    }
    return os;
}
