#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  S21CalocMatrix(*this, 3, 3);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = 0;
}

S21Matrix::S21Matrix(int rows, int cols) {
  S21CalocMatrix(*this, rows, cols);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = 0;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  S21CalocMatrix(*this, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  clean(*this);
}

void S21Matrix::clean(S21Matrix& other){
    if (other.matrix_) {
        for (int i = 0; i < other.rows_; i++) delete[] other.matrix_[i];
        delete[] other.matrix_;
        other.rows_ = 0;
        other.cols_ = 0;
      }
}

double S21Matrix::Determinant() {
  double res = 0;
  if (rows_ != cols_)
    throw std::invalid_argument("matrix is not square");
  else {
    S21Matrix copy(rows_, cols_);

    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) copy.matrix_[i][j] = matrix_[j][i];

    if (rows_ == 1)
      res = matrix_[0][0];
    else {
      res = 1;
      copy.S21GetMatrix();
      for (int i = 0; i < rows_; i++) res *= copy.matrix_[i][i];
    }
  }
  return res;
}

void S21Matrix::S21GetMatrix() {
  for (int i = 0; i < rows_; i++) {
    if (!matrix_[i][i]) {
      for (int j = i + 1; j < rows_; j++) {
        for (int k = 0; k < rows_; k++) matrix_[i][k] += matrix_[j][k];
      }
    }
    if (matrix_[i][i]) {
      for (int j = i + 1; j < rows_; j++) {
        double factor = matrix_[j][i] / matrix_[i][i];
        for (int k = 0; k < rows_; k++) matrix_[j][k] -= matrix_[i][k] * factor;
      }
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix n(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) n.matrix_[i][j] = matrix_[j][i];
  return n;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix calc(rows_, cols_);
  double d = 0;

  if (rows_ != cols_) throw std::invalid_argument("matrix is not square");
  if (rows_ == 1) {
    calc(1, 1);
    calc.matrix_[0][0] = 1;
    return calc;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      calc.matrix_[i][j] = MatrixMinor(i, j).Determinant() * pow(-1, i + j);
    }
  }

  return calc;
}

S21Matrix S21Matrix::MatrixMinor(int irows, int jcols) {
  int rows = rows_ - 1, cols = cols_ - 1;
  if (rows_ == 1) rows = 1;
  if (cols_ == 1) cols = 1;
  S21Matrix minor(rows, cols);

  for (int i = 0, mi = 0; i < rows_; i++) {
    if (i != irows) {
      for (int j = 0, mj = 0; j < cols_; j++) {
        if (j != jcols) {
          minor.matrix_[mi][mj] = matrix_[i][j];
          mj++;
        }
      }
      mi++;
    }
  }
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix result(rows_, cols_);
  double det = Determinant();
  if (rows_ < 2) throw std::invalid_argument("Error, incorrect matrix");
  if (!det) throw std::runtime_error("matrix determinant is 0");
  result = CalcComplements().Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

//__________________________________________________________________________________
int S21Matrix::getCols() const { return cols_; }

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::setSize(int x, int y) {
  if (x <= 0 || y <= 0)
    throw std::invalid_argument("Invalid argument different matrix dimensions");
  if (x == rows_ && y == cols_) return 0;

  S21Matrix copy(x,y);
  for (int i = 0; i < rows_ && i< x; i++)
    for (int j = 0; j < cols_ && j< y; j++) copy.matrix_[i][j] = matrix_[i][j];

  *this = copy;

  return 0;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) return false;
  return true;
}

void S21Matrix::S21CalocMatrix(S21Matrix& other, int rows, int cols) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Invalid argument different matrix dimensions");
  else {
    other.rows_ = rows;
    other.cols_ = cols;
    other.matrix_ = new double*[other.rows_];
    for (int i = 0; i < other.rows_; i++)
      other.matrix_[i] = new double[other.cols_];
  }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::invalid_argument("Invalid argument different matrix dimensions");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Invalid argument different matrix dimensions");
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::DivNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] /= num;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (rows_ != other.cols_)
    throw std::invalid_argument("Invalid argument different matrix dimensions");
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      for (int k = 0; k < other.rows_; k++)
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
  *this = res;
}

//__________________________________________________________________________________

const double& S21Matrix::operator()(int x, int y) const {
  if (x > rows_ || x < 0 || y > cols_ || y < 0)
    throw std::out_of_range("Index per matrix difference");
  return matrix_[x][y];
}

double& S21Matrix::operator()(int x, int y) {
  if (x > rows_ || x < 0 || y > cols_ || y < 0)
    throw std::out_of_range("Index per matrix difference");
  return matrix_[x][y];
}

S21Matrix S21Matrix::operator*(const double x) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[i][j] = matrix_[i][j];
  res.MulNumber(x);
  return res;
}

S21Matrix S21Matrix::operator/(double x) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[i][j] = matrix_[i][j];
  res.DivNumber(x);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[i][j] = matrix_[i][j];
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res = *this;
  res.SumMatrix(other);
  return res;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[i][j] = matrix_[i][j];
  res.SubMatrix(other);
  return res;
}
bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }


S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if(*this == other) return *this;
  clean(*this);
  S21CalocMatrix(*this,other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this ;
}

// S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//   S21Matrix a(other.rows_, other.cols_);
//   for (int i = 0; i < rows_; i++) {
//     for (int j = 0; j < cols_; j++) {
//       a.matrix_[i][j] = other.matrix_[i][j];
//     }
//   }
//   return *this ;
// }

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}
S21Matrix& S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}
S21Matrix& S21Matrix::operator/=(const double other) {
  DivNumber(other);
  return *this;
}