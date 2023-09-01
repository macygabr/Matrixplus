#ifndef CPP1_S21_MATRIXPLUS_1_SRC_S21_MSTRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_SRC_S21_MSTRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_; /**< строки и колонки */
  double** matrix_; /**< поинтер на облость памяти  */

 private:
  // Support
  void S21CalocMatrix(S21Matrix& other, int rows,
                      int cols); /**< Выделение памяти*/
  void S21GetMatrix(); /**< Приведение матрицы к треугольному виду*/
  S21Matrix MatrixMinor(int rows, int cols);
  void clean(S21Matrix& other);

 public:
  // Accessor and Mutator:
  int getCols() const; /**< Возвращает число колонок*/
  int getRows() const; /**< Возвращает число строк */
  int setSize(int x, int y); /**< Присвоение размерности матрицы */

  // Operations
  bool EqMatrix(const S21Matrix& other)
      const; /**< Проверяет матрицы на равенство между собой */
  void SumMatrix(
      const S21Matrix& other); /**< Прибавляет вторую матрицы к текущей */
  void SubMatrix(
      const S21Matrix& other); /**< Вычитает из текущей матрицы другую */
  void MulNumber(const double num); /**< Умножает текущую матрицу на число */
  void DivNumber(const double num); /**< Делит текущую матрицу на число */
  void MulMatrix(
      const S21Matrix& other); /**< Умножает текущую матрицу на вторую */
  double
  Determinant(); /**< Вычисляет и возвращает определитель текущей матрицы */
  S21Matrix Transpose(); /**< Создает новую транспонированную матрицу из текущей
                            и возвращает ее */
  S21Matrix CalcComplements(); /**< Вычисляет матрицу алгебраических дополнений
                                  текущей матрицы и возвращает ее */
  S21Matrix InverseMatrix(); /**< Вычисляет и возвращает обратную матрицу */

  // Operators:
  S21Matrix operator*(const double x); /**< умножение матрицы на число */
  S21Matrix operator/(const double x); /**< деление матрицы на число */
  S21Matrix operator*(const S21Matrix& x); /**< Умножение матриц */
  S21Matrix operator+(const S21Matrix& x); /**< Сложение двух матриц */
  S21Matrix operator-(
      const S21Matrix& x); /**< Вычитание одной матрицы из другой */
  bool operator==(const S21Matrix& x); /**< Проверка на равенство матриц */
  S21Matrix& operator=(
      const S21Matrix& x); /**< Присвоение матрице значений другой матрицы */
  S21Matrix& operator/=(const double x); /**< Присвоение деления */
  S21Matrix& operator*=(const double x); /**< Присвоение умножения */
  S21Matrix operator+=(const S21Matrix& x); /**< Присвоение сложения */
  S21Matrix operator-=(const S21Matrix& x); /**< Присвоение разности */
  S21Matrix operator*=(const S21Matrix& x); /**< Присвоение умножения */
  const double& operator()(
      int x, int y) const; /**<  Индексация по элементам постоянной матрицы */
  double& operator()(int x, int y); /**<  Индексация по элементам матрицы */

  // Constructors:
  S21Matrix(); /**<Базовый конструктор, инициализирующий матрицу некоторой
                  заранее заданной размерностью*/
  S21Matrix(int rows, int cols); /**<Параметризированный конструктор с
                                    количеством строк и столбцов*/
  S21Matrix(const S21Matrix& other); /**<Конструктор копирования*/
  S21Matrix(S21Matrix&& other); /**< Конструктор переноса*/
  ~S21Matrix();                 /**<Деструктор*/
};

#endif