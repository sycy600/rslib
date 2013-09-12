// Copyright 2013 sycy600

#include "rslib/polynomial.h"
#include <vector>
#include "gtest/gtest.h"

TEST(Polynomial, Empty) {
  // Polynomial cannot be empty, there must always at least one element.
  std::vector<int> coeff;
  ASSERT_THROW((rslib::Polynomial<int>(coeff)), rslib::PolynomialException);
}

TEST(Polynomial, ZeroCoeffs) {
  // All zero coefficients will be thrown away from the highest positions
  // of polynomial.
  std::vector<int> coeff = {1, 0};
  rslib::Polynomial<int> p(coeff);
  ASSERT_EQ(p.degree(), 0u);
  ASSERT_EQ(p.getValue(0), 1);
}

TEST(Polynomial, OnlyZeroCoeffs) {
  // If there are only zero coefficients then first zero will remain and
  // the result is 0 polynomial.
  std::vector<int> coeff = {0, 0};
  rslib::Polynomial<int> p(coeff);
  ASSERT_EQ(p.degree(), 0u);
  ASSERT_EQ(p.getValue(0), 0);
}

TEST(Polynomial, Degree) {
  std::vector<int> coeff = {1, 1};
  rslib::Polynomial<int> p(coeff);
  ASSERT_EQ(p.degree(), 1u);
}

TEST(Polynomial, GetValue) {
  // p(x) = 2x + 1
  std::vector<int> coeff = {1, 2};
  rslib::Polynomial<int> p(coeff);
  // p_0 = 1
  // p_1 = 2
  ASSERT_EQ(p.getValue(0), 1);
  ASSERT_EQ(p.getValue(1), 2);
}

TEST(Polynomial, SetValue) {
  std::vector<int> coeff = {1, 2};
  rslib::Polynomial<int> p(coeff);
  ASSERT_EQ(p.getValue(0), 1);
  p.setValue(0, 4);
  ASSERT_EQ(p.getValue(0), 4);
}

TEST(Polynomial, Evaluate) {
  // Check polynomial evaluation.
  // p(x) = 2x + 1
  std::vector<int> coeff = {1, 2};
  rslib::Polynomial<int> p(coeff);
  // p(4) = 2 * 4 + 1 = 9
  int result = p.evaluate(4);
  ASSERT_EQ(result, 9);
}

TEST(Polynomial, Add) {
  // Check adding of polynomials when they have the same degree.
  rslib::Polynomial<int> first({1, 2});
  rslib::Polynomial<int> second({3, 4});
  ASSERT_EQ(first + second, rslib::Polynomial<int>({4, 6}));
}

TEST(Polynomial, AddFirstPolynomialGreater) {
  // Check adding of polynomials when first is greater than second.
  rslib::Polynomial<int> first({1, 2, 3});
  rslib::Polynomial<int> second({3, 4});
  ASSERT_EQ(first + second, rslib::Polynomial<int>({4, 6, 3}));
}

TEST(Polynomial, AddSecondPolynomialGreater) {
  // Check adding of polynomials when second is greater than first.
  rslib::Polynomial<int> first({1, 2});
  rslib::Polynomial<int> second({3, 4, 3});
  ASSERT_EQ(first + second, rslib::Polynomial<int>({4, 6, 3}));
}

TEST(Polynomial, AddNegativePolynomials) {
  // The result will be cleaned to simple 0 polynomial.
  rslib::Polynomial<int> first({-3, -4, -3});
  rslib::Polynomial<int> second({3, 4, 3});
  ASSERT_EQ(first + second, rslib::Polynomial<int>({0}));
}

TEST(Polynomial, CheckEqualIfNotEqual) {
  rslib::Polynomial<int> first({1, 2});
  rslib::Polynomial<int> second({3, 4, 3});
  ASSERT_FALSE(first == second);
  ASSERT_TRUE(first != second);
}

TEST(Polynomial, CheckEqualIfEqual) {
  rslib::Polynomial<int> first({1, 2});
  rslib::Polynomial<int> second({1, 2});
  ASSERT_TRUE(first == second);
  ASSERT_FALSE(first != second);
}
