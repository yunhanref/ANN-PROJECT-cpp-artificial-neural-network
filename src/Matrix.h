#pragma once
#include "Exceptions.h"
#include <iostream>
public:
    int rows;
    int cols;
    double* data;

    Matrix(int r, int c);
    ~Matrix() noexcept;
    
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    double& at(int r, int c);
    const double& at(int r, int c) const;
    double& operator()(int r, int c);
    const double& operator()(int r, int c) const;

    Matrix operator*(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const; 
    Matrix operator-(const Matrix& other) const;

    Matrix operator*(double scalar) const;
    Matrix operator+(double scalar) const;
    Matrix operator-(double scalar) const;
    Matrix operator/(double scalar) const;

    friend Matrix operator*(double scalar, const Matrix& matrix);
    friend Matrix operator+(double scalar, const Matrix& matrix);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix transpose() const;
    Matrix hadamard(const Matrix& other) const;
    void randomize(double minVal = -1.0, double maxVal = 1.0);
    
    void print() const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

