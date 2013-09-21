// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

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

TEST(Polynomial, CreatingPolynomialWithoutGivingCoefficient) {
  // 0 degree polynomial with single 0 value is created.
  rslib::Polynomial<int> p({0});
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

TEST(Polynomial, SetValueOutOfLimit) {
  std::vector<int> coeff = {0};
  rslib::Polynomial<int> p(coeff);
  p.setValue(3, 4);
  ASSERT_EQ(p, rslib::Polynomial<int>({0, 0, 0, 4}));
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

TEST(Polynomial, SubtractPolynomials) {
  rslib::Polynomial<int> first({4});
  rslib::Polynomial<int> second({3, 4, 3});
  ASSERT_EQ(first - second, rslib::Polynomial<int>({1, -4, -3}));
}

TEST(Polynomial, SubtractFromZeroPolynomial) {
  rslib::Polynomial<int> first({0});
  rslib::Polynomial<int> second({3, 4, 3});
  ASSERT_EQ(first - second, rslib::Polynomial<int>({-3, -4, -3}));
}

TEST(Polynomial, CheckEqualIfNotEqual) {
  rslib::Polynomial<int> first({3, 4, 2});
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

TEST(Polynomial, MultiplicationWithFirstPolynomialBigger) {
  rslib::Polynomial<int> first({5, 0, 0, 2, 3, 1});
  rslib::Polynomial<int> second({-3, 1});
  ASSERT_EQ(first * second, rslib::Polynomial<int>({-15, 5, 0, -6, -7, 0, 1}));
}

TEST(Polynomial, MultiplicationWithSecondPolynomialBigger) {
  rslib::Polynomial<int> first({-3, 1});
  rslib::Polynomial<int> second({5, 0, 0, 2, 3, 1});
  ASSERT_EQ(first * second, rslib::Polynomial<int>({-15, 5, 0, -6, -7, 0, 1}));
}

TEST(Polynomial, MultiplicationWithFirstZero) {
  rslib::Polynomial<int> first({0});
  rslib::Polynomial<int> second({4, 1});
  ASSERT_EQ(first * second, rslib::Polynomial<int>({0}));
}

TEST(Polynomial, MultiplicationWithSecondZero) {
  rslib::Polynomial<int> first({4, 1});
  rslib::Polynomial<int> second({0});
  ASSERT_EQ(first * second, rslib::Polynomial<int>({0}));
}

TEST(Polynomial, MultiplicationWithOneElementPolynomials) {
  rslib::Polynomial<int> first({4});
  rslib::Polynomial<int> second({3});
  ASSERT_EQ(first * second, rslib::Polynomial<int>({12}));
}

TEST(Polynomial, Division) {
  rslib::Polynomial<int> first({1, 6, 2});
  rslib::Polynomial<int> second({2, 1});
  ASSERT_EQ(first / second, rslib::Polynomial<int>({2, 2}));
}

TEST(Polynomial, DivisionByZero) {
  rslib::Polynomial<int> first({1, 6, 2});
  rslib::Polynomial<int> second({0});
  ASSERT_THROW(first / second, rslib::PolynomialException);
}

TEST(Polynomial, DivisionSmallerPolynomialByBiggerPolynomial) {
  rslib::Polynomial<int> first({2, 1});
  rslib::Polynomial<int> second({1, 6, 2});
  ASSERT_EQ(first / second, rslib::Polynomial<int>({0}));
}

TEST(Polynomial, DivisionOneElementPolynomials) {
  rslib::Polynomial<int> first({8});
  rslib::Polynomial<int> second({4});
  ASSERT_EQ(first / second, rslib::Polynomial<int>({2}));
}

TEST(Polynomial, DivisionOneElementPolynomialsWithFloatingPointNumbers) {
  rslib::Polynomial<double> first({9.0});
  rslib::Polynomial<double> second({4.0});
  ASSERT_EQ(first / second, rslib::Polynomial<double>({2.25}));
}

TEST(Polynomial, Modulo) {
  rslib::Polynomial<int> first({2, 3, 2});
  rslib::Polynomial<int> second({3, 1});
  ASSERT_EQ(first % second, rslib::Polynomial<int>({11}));
}

TEST(Polynomial, ModuloSmallerPolynomialByBiggerPolynomial) {
  rslib::Polynomial<int> first({3, 1});
  rslib::Polynomial<int> second({2, 3, 2});
  ASSERT_EQ(first % second, rslib::Polynomial<int>({3, 1}));
}

TEST(Polynomial, ModuloZeroPolynomialByPolynomial) {
  rslib::Polynomial<int> first({0});
  rslib::Polynomial<int> second({2, 3, 2});
  ASSERT_EQ(first % second, rslib::Polynomial<int>({0}));
}

TEST(Polynomial, PrintPolynomial) {
  rslib::Polynomial<int> p({3, 4, 5});
  std::ostringstream iss;
  iss << p;
  ASSERT_EQ(iss.str(), "[3,4,5,]");
}

TEST(Polynomial, Iterators) {
  rslib::Polynomial<int> p({3, 4, 5});
  rslib::Polynomial<int>::iterator it = p.begin();
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(it, p.end());
}

TEST(Polynomial, ConstIterators) {
  const rslib::Polynomial<int> p({3, 4, 5});
  rslib::Polynomial<int>::const_iterator it = p.begin();
  ASSERT_EQ(*it, 3);
  ++it;
  ASSERT_EQ(*it, 4);
  ++it;
  ASSERT_EQ(*it, 5);
  ++it;
  ASSERT_EQ(it, p.end());
}
