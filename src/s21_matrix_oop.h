#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#define EPS 10E-7

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 public:
  // Constructors and deconstructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Accessors
  int getRows() const;
  int getCols() const;

  // Mutators
  void setRows(const int rows);
  void setCols(const int cols);

  // Functions
  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix Minor(const int i, const int j);

  // Operators
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double& num) noexcept;
  bool operator==(const S21Matrix& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double& num) noexcept;
  double operator()(const int i, const int j) const;
  double& operator()(const int i, const int j);

 private:
  int rows_, cols_;
  double** matrix_;

  double** allocate(const int rows, const int cols);
  void deallocate(const int rows);
};

S21Matrix operator*(const double& num, const S21Matrix& other);

#endif  // S21_MATRIX_OOP_H_