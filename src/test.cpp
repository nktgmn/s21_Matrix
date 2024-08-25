#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;
  EXPECT_EQ(mat.getRows(), 1);
  EXPECT_EQ(mat.getCols(), 1);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0.0);
}

TEST(S21MatrixTest, ParamsConstructor_0) {
  S21Matrix mat(2, 2);
  EXPECT_EQ(mat.getRows(), 2);
  EXPECT_EQ(mat.getCols(), 2);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0.0);
}

TEST(S21MatrixTest, ParamsConstructor_1) {
  EXPECT_THROW(S21Matrix mat(0, 2), std::invalid_argument);
}

TEST(S21MatrixTest, ParamsConstructor_2) {
  EXPECT_THROW(S21Matrix mat(1, -3), std::invalid_argument);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix mat(2, 2);
  S21Matrix copy = S21Matrix(mat);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix mat(2, 2);
  S21Matrix copy = std::move(mat);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 2);
}

TEST(S21MatrixTest, SetRows_0) {
  S21Matrix mat;
  mat.setRows(2);
  EXPECT_EQ(mat.getRows(), 2);
}

TEST(S21MatrixTest, SetRows_1) {
  S21Matrix mat;
  mat.setRows(1);
  EXPECT_EQ(mat.getRows(), 1);
}

TEST(S21MatrixTest, SetRows_2) {
  S21Matrix mat;
  EXPECT_THROW(mat.setRows(0), std::invalid_argument);
}

TEST(S21MatrixTest, SetCols_0) {
  S21Matrix mat;
  mat.setCols(2);
  EXPECT_EQ(mat.getCols(), 2);
}

TEST(S21MatrixTest, SetCols_1) {
  S21Matrix mat;
  mat.setCols(1);
  EXPECT_EQ(mat.getCols(), 1);
}

TEST(S21MatrixTest, SetCols_2) {
  S21Matrix mat;
  EXPECT_THROW(mat.setCols(0), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorSet_0) {
  S21Matrix mat(2, 2);
  EXPECT_THROW(mat(-1, 1), std::out_of_range);
}

TEST(S21MatrixTest, OperatorSet_1) {
  S21Matrix mat(2, 2);
  EXPECT_THROW(mat(1, -1), std::out_of_range);
}

TEST(S21MatrixTest, OperatorSet_2) {
  S21Matrix mat(2, 2);
  mat(1, 1) = 5;
  EXPECT_DOUBLE_EQ(mat(1, 1), 5);
}

TEST(S21MatrixTest, Operator_Get_0) {
  const S21Matrix mat(2, 2);
  EXPECT_THROW(mat(-1, 1), std::out_of_range);
}

TEST(S21MatrixTest, Operator_Get_1) {
  const S21Matrix mat(2, 2);
  EXPECT_THROW(mat(1, -1), std::out_of_range);
}

TEST(S21MatrixTest, Operator_Get_2) {
  S21Matrix mat(2, 2);
  mat(1, 1) = 5;
  const S21Matrix constMat = mat;
  EXPECT_DOUBLE_EQ(constMat(1, 1), 5);
}

TEST(S21MatrixTest, MulNumber) {
  S21Matrix mat(2, 2);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(1, 0) = 2;
  mat(1, 1) = 3;
  mat.MulNumber(2);
  EXPECT_DOUBLE_EQ(mat(0, 0), 0);
  EXPECT_DOUBLE_EQ(mat(0, 1), 2);
  EXPECT_DOUBLE_EQ(mat(1, 0), 4);
  EXPECT_DOUBLE_EQ(mat(1, 1), 6);
}

TEST(S21MatrixTest, EqMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, EqMatrix_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  EXPECT_TRUE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, EqMatrix_2) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 4;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  EXPECT_FALSE(mat1.EqMatrix(mat2));
}

TEST(S21MatrixTest, Transpose) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 1;
  mat2(1, 1) = 3;

  S21Matrix mat3 = mat1.Transpose();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, SumMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_THROW(mat1.SumMatrix(mat2), std::invalid_argument);
}

TEST(S21MatrixTest, SumMatrix_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 3;
  mat3(0, 1) = 5;
  mat3(1, 0) = 7;
  mat3(1, 1) = 9;

  mat1.SumMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, SubMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 3);
  EXPECT_THROW(mat1.SubMatrix(mat2), std::invalid_argument);
}

TEST(S21MatrixTest, SubMatrix_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = -3;
  mat3(0, 1) = -3;
  mat3(1, 0) = -3;
  mat3(1, 1) = -3;

  mat1.SubMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, MulMatrix_0) {
  S21Matrix mat1(2, 2);
  S21Matrix mat2(3, 2);
  EXPECT_THROW(mat1.MulMatrix(mat2), std::domain_error);
}

TEST(S21MatrixTest, MulMatrix_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 5;
  mat3(0, 1) = 6;
  mat3(1, 0) = 21;
  mat3(1, 1) = 26;

  mat1.MulMatrix(mat2);

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, Minor_0) {
  S21Matrix mat1(2, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.Minor(2, 1), std::out_of_range);
}

TEST(S21MatrixTest, Minor_1) {
  S21Matrix mat1(2, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.Minor(1, 2), std::out_of_range);
}

TEST(S21MatrixTest, Minor_2) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(0, 2) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  mat1(1, 2) = 5;
  mat1(2, 0) = 6;
  mat1(2, 1) = 7;
  mat1(2, 2) = 8;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 6;
  mat2(1, 1) = 8;

  S21Matrix mat3 = mat1.Minor(1, 1);

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, Determinant_0) {
  S21Matrix mat1(3, 2);
  EXPECT_THROW(mat1.Determinant(), std::domain_error);
}

TEST(S21MatrixTest, Determinant_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  double det = mat1.Determinant();

  EXPECT_DOUBLE_EQ(det, -2);
}

TEST(S21MatrixTest, CalcComplements_0) {
  S21Matrix mat1(3, 2);
  EXPECT_THROW(S21Matrix mat2 = mat1.CalcComplements(), std::domain_error);
}

TEST(S21MatrixTest, CalcComplements_1) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(0, 2) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  mat1(1, 2) = 5;
  mat1(2, 0) = 6;
  mat1(2, 1) = 7;
  mat1(2, 2) = 8;

  S21Matrix mat2(3, 3);
  mat2(0, 0) = -3;
  mat2(0, 1) = 6;
  mat2(0, 2) = -3;
  mat2(1, 0) = 6;
  mat2(1, 1) = -12;
  mat2(1, 2) = 6;
  mat2(2, 0) = -3;
  mat2(2, 1) = 6;
  mat2(2, 2) = -3;

  S21Matrix mat3 = mat1.CalcComplements();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, CalcComplements_2) {
  S21Matrix mat1;

  S21Matrix mat2;
  mat2(0, 0) = 1;

  S21Matrix mat3 = mat1.CalcComplements();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, Inverse_0) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(0, 2) = 2;
  mat1(1, 0) = 3;
  mat1(1, 1) = 4;
  mat1(1, 2) = 5;
  mat1(2, 0) = 6;
  mat1(2, 1) = 7;
  mat1(2, 2) = 8;

  EXPECT_THROW(S21Matrix mat2 = mat1.InverseMatrix(), std::domain_error);
}

TEST(S21MatrixTest, Inverse_1) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 2;
  mat1(0, 1) = 5;
  mat1(0, 2) = 7;
  mat1(1, 0) = 6;
  mat1(1, 1) = 3;
  mat1(1, 2) = 4;
  mat1(2, 0) = 5;
  mat1(2, 1) = -2;
  mat1(2, 2) = -3;

  S21Matrix mat2(3, 3);
  mat2(0, 0) = 1;
  mat2(0, 1) = -1;
  mat2(0, 2) = 1;
  mat2(1, 0) = -38;
  mat2(1, 1) = 41;
  mat2(1, 2) = -34;
  mat2(2, 0) = 27;
  mat2(2, 1) = -29;
  mat2(2, 2) = 24;

  S21Matrix mat3 = mat1.InverseMatrix();

  EXPECT_TRUE(mat3.EqMatrix(mat2));
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 3;
  mat3(0, 1) = 5;
  mat3(1, 0) = 7;
  mat3(1, 1) = 9;

  mat1 += mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMinuxEqual) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = -3;
  mat3(0, 1) = -3;
  mat3(1, 0) = -3;
  mat3(1, 1) = -3;

  mat1 -= mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMultEqNumber) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  mat1 *= 2;

  EXPECT_TRUE(mat2.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorMultEqMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 5;
  mat3(0, 1) = 6;
  mat3(1, 0) = 21;
  mat3(1, 1) = 26;

  mat1 *= mat2;

  EXPECT_TRUE(mat3.EqMatrix(mat1));
}

TEST(S21MatrixTest, OperatorDoubleEq) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorEq_0) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 4;
  mat2(0, 1) = 5;
  mat2(1, 0) = 6;
  mat2(1, 1) = 7;

  mat1 = mat2;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorEq_1) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 1;
  mat2(1, 0) = 2;
  mat2(1, 1) = 3;

  mat2 = mat1;

  EXPECT_TRUE(mat1 == mat2);
}

TEST(S21MatrixTest, OperatorMultMatrix) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 3;
  mat2(0, 1) = 4;
  mat2(1, 0) = 5;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 5;
  mat3(0, 1) = 6;
  mat3(1, 0) = 21;
  mat3(1, 1) = 26;

  S21Matrix mat4 = mat1 * mat2;

  EXPECT_TRUE(mat3 == mat4);
}

TEST(S21MatrixTest, OperatorMultNumber) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3 = mat1 * 2;
  S21Matrix mat4 = 2 * mat1;

  EXPECT_TRUE(mat2 == mat3);
  EXPECT_TRUE(mat2 == mat4);
}

TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 0;
  mat3(0, 1) = 3;
  mat3(1, 0) = 6;
  mat3(1, 1) = 9;

  S21Matrix mat4 = mat1 + mat2;

  EXPECT_TRUE(mat3 == mat4);
}

TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix mat1(2, 2);
  mat1(0, 0) = 0;
  mat1(0, 1) = 1;
  mat1(1, 0) = 2;
  mat1(1, 1) = 3;

  S21Matrix mat2(2, 2);
  mat2(0, 0) = 0;
  mat2(0, 1) = 2;
  mat2(1, 0) = 4;
  mat2(1, 1) = 6;

  S21Matrix mat3(2, 2);
  mat3(0, 0) = 0;
  mat3(0, 1) = -1;
  mat3(1, 0) = -2;
  mat3(1, 1) = -3;

  S21Matrix mat4 = mat1 - mat2;

  EXPECT_TRUE(mat3 == mat4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}