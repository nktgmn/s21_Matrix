#include "s21_matrix_oop.h"

double** S21Matrix::allocate(const int rows, const int cols) {
  double** matrix = new double*[rows];
  if (matrix == nullptr) {
    throw std::bad_alloc();
  }

  int k = 0;

  try {
    for (int i = 0; i < rows; ++i) {
      matrix[i] = new double[cols];
      if (matrix[i] == nullptr) {
        k = i;
        throw std::bad_alloc();
      }
      for (int j = 0; j < cols; ++j) {
        matrix[i][j] = 0;
      }
    }
  } catch (...) {
    for (int i = 0; i < k; ++i) {
      if (matrix[i] != nullptr) {
        delete[] matrix[i];
      }
    }
    delete[] matrix;
    throw;
  }

  return matrix;
}

void S21Matrix::deallocate(const int rows) {
  for (int i = 0; i < rows; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix() {
  rows_ = 1;
  cols_ = 1;
  matrix_ = allocate(rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1) {
    throw std::invalid_argument("Invalid rows argument");
  }

  if (cols < 1) {
    throw std::invalid_argument("Invalid cols argument");
  }

  rows_ = rows;
  cols_ = cols;
  matrix_ = allocate(rows_, cols_);
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    deallocate(rows_);
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = allocate(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Invalid rows argument");
  }

  if (rows_ == rows) {
    return;
  }

  double** new_matrix = allocate(rows, cols_);

  for (int i = 0; i < rows && i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }

  deallocate(rows_);
  matrix_ = new_matrix;
  rows_ = rows;
}

void S21Matrix::setCols(const int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Invalid cols argument");
  }

  if (cols_ == cols) {
    return;
  }

  double** new_matrix = allocate(rows_, cols);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_ && j < cols; ++j) {
      new_matrix[i][j] = matrix_[i][j];
    }
  }

  deallocate(rows_);
  matrix_ = new_matrix;
  cols_ = cols;
}

double S21Matrix::operator()(const int i, const int j) const {
  if ((i < 0) || (i > rows_ - 1)) {
    throw std::out_of_range("i argument out of range");
  }

  if ((j < 0) || (j > cols_ - 1)) {
    throw std::out_of_range("j argument out of range");
  }

  return matrix_[i][j];
}

double& S21Matrix::operator()(const int i, const int j) {
  if ((i < 0) || (i > rows_ - 1)) {
    throw std::out_of_range("i argument out of range");
  }

  if ((j < 0) || (j > cols_ - 1)) {
    throw std::out_of_range("j argument out of range");
  }

  double& value = matrix_[i][j];

  return value;
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        return false;
      }
    }
  }

  return true;
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix new_matrix(cols_, rows_);

  for (int i = 0; i < cols_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      new_matrix.matrix_[i][j] = matrix_[j][i];
    }
  }

  return new_matrix;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::invalid_argument("SumMatrix: different dimensions");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::invalid_argument("SumMatrix: different dimensions");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (other.rows_ != cols_) {
    throw std::domain_error("MulMatrix: cannot multiply matrices");
  }

  double** new_matrix = allocate(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        new_matrix[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  setCols(other.cols_);
  deallocate(rows_);
  matrix_ = new_matrix;
}

S21Matrix S21Matrix::Minor(const int i, const int j) {
  if ((i < 0) || (i > rows_ - 1)) {
    throw std::out_of_range("Minor: i argument out of range");
  }

  if ((j < 0) || (j > cols_ - 1)) {
    throw std::out_of_range("Minor: j argument out of range");
  }

  S21Matrix minor(rows_ - 1, cols_ - 1);

  for (int m = 0; m < rows_; ++m) {
    for (int n = 0; n < cols_; ++n) {
      if ((m < i) && (n < j)) {
        minor(m, n) = matrix_[m][n];
      } else if ((m > i) && (n < j)) {
        minor(m - 1, n) = matrix_[m][n];
      } else if ((m < i) && (n > j)) {
        minor(m, n - 1) = matrix_[m][n];
      } else if ((m > i) && (n > j)) {
        minor(m - 1, n - 1) = matrix_[m][n];
      }
    }
  }

  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::domain_error("Determinant: matrix must be squared");
  }

  double det = 0;

  if (rows_ == 1) {
    det += matrix_[0][0];
  } else {
    for (int i = 0; i < cols_; ++i) {
      S21Matrix minor = this->Minor(0, i);
      det += minor.Determinant() * pow(-1, i) * matrix_[0][i];
    }
  }

  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::domain_error("CalcComplements: matrix must be squared");
  }

  S21Matrix new_matrix(rows_, cols_);

  if (rows_ == 1) {
    new_matrix(0, 0) = 1;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix minor = this->Minor(i, j);
        new_matrix.matrix_[i][j] = minor.Determinant() * pow(-1, i + j);
      }
    }
  }

  return new_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();

  if (fabs(det) < EPS) {
    throw std::domain_error("InverseMatrix: matrix determinant is zero");
  }

  S21Matrix compl_matrix = this->CalcComplements();

  S21Matrix transp_matrix = compl_matrix.Transpose();

  transp_matrix.MulNumber(1 / det);

  return transp_matrix;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double& num) noexcept {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) noexcept {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res += other;
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res -= other;
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res *= other;
  return res;
}

S21Matrix S21Matrix::operator*(const double& num) noexcept {
  S21Matrix res(*this);
  res *= num;
  return res;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this == &other) {
    return *this;
  }

  deallocate(rows_);

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = allocate(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix operator*(const double& num, const S21Matrix& other) {
  S21Matrix res(other);
  res *= num;
  return res;
}
