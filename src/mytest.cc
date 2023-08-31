#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

void writeMatrix(double* seq, S21Matrix& other, int col, int row) {
  int n = 0;
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < row; j++) {
      other(i, j) = seq[n++];
    }
  }
}

// TEST(TestGroupName, Brackets) {
//   S21Matrix a(1, 1);
//   S21Matrix b(1, 1);
//   a(0, 0) = 1.2;
//   b(0, 0) = 1.2;
//   ASSERT_EQ(a.EqMatrix(b), true);
// }

// TEST(TestGroupName, Mutator) {
  // S21Matrix a;
  // S21Matrix b;
  // a.setSize(1, 1);
  // b.setSize(1, 1);
  // a(0, 0) = 1.2;
  // b(0, 0) = 1.2;
  // ASSERT_EQ(a.EqMatrix(b), true);

  // EXPECT_EQ(a.getCols(), 1);
  // EXPECT_EQ(a.getRows(), 1);

  // EXPECT_EQ(b.getCols(), 1);
  // EXPECT_EQ(b.getRows(), 1);
// }

// TEST(Matrix, Copy) {
//   S21Matrix basic(2, 2);
//   double seq[] = {11.11, 12.12, 21.21, 22.22};
//   writeMatrix(seq, basic, 2, 2);

//   S21Matrix copy(basic);
//   ASSERT_EQ(basic.EqMatrix(copy), true);
// }

TEST(Matrix, Move) {
  S21Matrix basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 22.22};
  writeMatrix(seq, basic, 2, 2);
  S21Matrix copy(basic);
  S21Matrix move(std::move(basic));
  ASSERT_EQ(copy.EqMatrix(move), true);
}

// TEST(Matrix, Inverse) {
//   S21Matrix basic(3, 3);
//   S21Matrix res(3, 3);
//   double bas[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
//   double result[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
//   writeMatrix(bas, basic, 3, 3);
//   writeMatrix(result, res, 3, 3);
//   basic = basic.InverseMatrix();
//   ASSERT_EQ(res == basic, true);
// }

// TEST(Matrix, CalcComplements) {
//   S21Matrix first(3, 3);
//   S21Matrix res(3, 3);
//   double f[] = {1, 2, 3, 4, 1, 5, 1, 1, 1};
//   double result[] = {-4, 1, 3, 1, -2, 1, 7, 7, -7};
//   writeMatrix(f, first, 3, 3);
//   writeMatrix(result, res, 3, 3);
//   first = first.CalcComplements();
//   ASSERT_EQ(first == res, true);
// }

// TEST(Matrix, Determinant) {
//   S21Matrix first(4, 4);
//   double f[] = {1, 2, 3, 4, 1, 5, 1, 1, 1, 1, 9, 1, 1, 1, 1, 11};
//   double res = 64;
//   writeMatrix(f, first, 4, 4);
//   EXPECT_EQ(res, first.Determinant());
// }

// TEST(Matrix, Operators) {
//   S21Matrix basic;
//   double bas[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//   writeMatrix(bas, basic, 3, 3);

//   S21Matrix sum(3, 3);
//   sum = basic * 3 - basic;
//   sum *= 0.5;
//   ASSERT_EQ(sum == basic, true);
//   sum += basic * 2;
//   sum = sum /= 3;

//   ASSERT_EQ(sum == basic, true);
//   sum *= 2;
//   sum /= 2;
//   sum *= sum;
//   sum -= basic;
//   sum += basic;
//   S21Matrix res;
//   double result[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
//   writeMatrix(result, res, 3, 3);

//   ASSERT_EQ(sum == res, true);
// }

// TEST(Matrix, Errors) {
  // S21Matrix error1(1, 5);
  // S21Matrix error2(2, 5);
  // S21Matrix error3(4, 4);
  // EXPECT_THROW(S21Matrix errors(-1, -1), std::invalid_argument);
  // EXPECT_THROW(S21Matrix errors(0, 0), std::invalid_argument);
  // EXPECT_THROW(error1 -= error2, std::invalid_argument);
  // EXPECT_THROW(error1 += error2, std::invalid_argument);
  // EXPECT_THROW(error1 *= error2, std::invalid_argument);
  // EXPECT_THROW(error1.Determinant(), std::invalid_argument);
  // EXPECT_THROW(error1.CalcComplements(), std::invalid_argument);
  // EXPECT_THROW(error3.InverseMatrix(), std::runtime_error);
  // EXPECT_THROW(error3(-12, 1) = 1, std::out_of_range);
  // EXPECT_THROW(error3(1, 123) = 14, std::out_of_range);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}