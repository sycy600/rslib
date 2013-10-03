// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>

class ExtendedFieldElementFixtureGF8 : public ::testing::Test {
 protected:
  // field GF(2)
  rslib::SimpleField sf = rslib::SimpleField(2);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator = rslib::Polynomial<rslib::SimpleFieldElement>({
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(0, sf),
                  rslib::SimpleFieldElement(1, sf)});

  // field GF(2^3) = GF(8)
  rslib::ExtendedField ef = rslib::ExtendedField(generator);
};

class ExtendedFieldElementFixtureGF9 : public ::testing::Test {
 protected:
  // field GF(3)
  rslib::SimpleField sf = rslib::SimpleField(3);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator = rslib::Polynomial<rslib::SimpleFieldElement>({
                  rslib::SimpleFieldElement(2, sf),
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(1, sf)});

  // field GF(3^2) = GF(9)
  rslib::ExtendedField ef = rslib::ExtendedField(generator);
};

TEST_F(ExtendedFieldElementFixtureGF8, PolynomialOfExtendedFieldElements) {
  rslib::Polynomial<rslib::ExtendedFieldElement>
      poly({rslib::ExtendedFieldElement(1, ef),
            rslib::ExtendedFieldElement(0, ef),
            rslib::ExtendedFieldElement(1, ef)});
  ASSERT_EQ(poly.getDegree(), 2u);
}

TEST_F(ExtendedFieldElementFixtureGF8, GetValue) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getValue(), 1u);
}

TEST_F(ExtendedFieldElementFixtureGF8, GetField) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getField(), ef);
}

TEST_F(ExtendedFieldElementFixtureGF8, Assign) {
  rslib::ExtendedFieldElement first(1, ef);
  rslib::ExtendedFieldElement second(2, ef);
  first = second;
  ASSERT_EQ(first.getValue(), 2u);
}

TEST_F(ExtendedFieldElementFixtureGF8, AssignToElementFromDifferentField) {
  // If one extended field element is assigned to the second one then they
  // have to be in the same field.
  rslib::ExtendedFieldElement first(1, ef);

  rslib::SimpleField sf(2);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator({rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(1, sf)});
  rslib::ExtendedField otherField(generator);

  rslib::ExtendedFieldElement second(1, otherField);
  ASSERT_THROW((first = second), rslib::ExtendedFieldElementException);
}

TEST_F(ExtendedFieldElementFixtureGF8, PolynomialRepresentation) {
  // 0 = 0
  ASSERT_EQ(rslib::ExtendedFieldElement(0, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // 1 = 1
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // A = A
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // A^2 = A^2
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(1, sf)}));

  // A^3 = A + 1
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // A^4 = A^2 + A
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(1, sf)}));

  // A^5 = A^2 + A + 1
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(1, sf)}));

  // A^6 = A^2 + 1
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(1, sf)}));
}

TEST_F(ExtendedFieldElementFixtureGF9, PolynomialRepresentationx) {
  // 0 = 0
  ASSERT_EQ(rslib::ExtendedFieldElement(0, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // 1 = 1
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // A = A
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(1, sf)}));

  // A^2 = 2A + 1
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(2, sf)}));

  // A^3 = 2A + 2
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(2, sf),
               rslib::SimpleFieldElement(2, sf)}));

  // A^4 = 2
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(2, sf),
               rslib::SimpleFieldElement(0, sf)}));

  // A^5 = 2A
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(0, sf),
               rslib::SimpleFieldElement(2, sf)}));

  // A^6 = A + 2
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(2, sf),
               rslib::SimpleFieldElement(1, sf)}));

  // A^7 = A + 1
  ASSERT_EQ(rslib::ExtendedFieldElement(8, ef).getPolynomialRepresentation(),
            rslib::Polynomial<rslib::SimpleFieldElement>(
              {rslib::SimpleFieldElement(1, sf),
               rslib::SimpleFieldElement(1, sf)}));
}

TEST_F(ExtendedFieldElementFixtureGF8, ZechLogarithms) {
  ASSERT_EQ(rslib::ExtendedFieldElement(0, ef).getZechLogarithm(),
            rslib::ZechLogarithm(0));
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getZechLogarithm(),
            rslib::ZechLogarithm(
              std::numeric_limits<unsigned int>::max()));
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getZechLogarithm(),
            rslib::ZechLogarithm(3));
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getZechLogarithm(),
            rslib::ZechLogarithm(6));
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getZechLogarithm(),
            rslib::ZechLogarithm(1));
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getZechLogarithm(),
            rslib::ZechLogarithm(5));
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getZechLogarithm(),
            rslib::ZechLogarithm(4));
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getZechLogarithm(),
            rslib::ZechLogarithm(2));
}

TEST_F(ExtendedFieldElementFixtureGF9, ZechLogarithms) {
  ASSERT_EQ(rslib::ExtendedFieldElement(0, ef).getZechLogarithm(),
            rslib::ZechLogarithm(0));
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getZechLogarithm(),
            rslib::ZechLogarithm(8));
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getZechLogarithm(),
            rslib::ZechLogarithm(7));
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getZechLogarithm(),
            rslib::ZechLogarithm(3));
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getZechLogarithm(),
            rslib::ZechLogarithm(5));
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getZechLogarithm(),
            rslib::ZechLogarithm(
              std::numeric_limits<unsigned int>::max()));
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getZechLogarithm(),
            rslib::ZechLogarithm(2));
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getZechLogarithm(),
            rslib::ZechLogarithm(1));
  ASSERT_EQ(rslib::ExtendedFieldElement(8, ef).getZechLogarithm(),
            rslib::ZechLogarithm(6));
}

TEST_F(ExtendedFieldElementFixtureGF8, Print) {
  std::ostringstream iss1;
  iss1 << rslib::ExtendedFieldElement(0, ef);
  ASSERT_EQ(iss1.str(), "0");

  std::ostringstream iss2;
  iss2 << rslib::ExtendedFieldElement(1, ef);
  ASSERT_EQ(iss2.str(), "1");

  std::ostringstream iss3;
  iss3 << rslib::ExtendedFieldElement(2, ef);
  ASSERT_EQ(iss3.str(), "A");

  std::ostringstream iss4;
  iss4 << rslib::ExtendedFieldElement(3, ef);
  ASSERT_EQ(iss4.str(), "A^2");
}

TEST_F(ExtendedFieldElementFixtureGF8, AddFirstArgumentBigger) {
  // A^3 = A + 1 in GF(8)
  rslib::ExtendedFieldElement first(2, ef);
  rslib::ExtendedFieldElement second(1, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(4, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, AddSecondArgumentBigger) {
  // A^3 = 1 + A in GF(8)
  rslib::ExtendedFieldElement first(1, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(4, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, AddWithZeroFirstArgument) {
  rslib::ExtendedFieldElement first(3, ef);
  rslib::ExtendedFieldElement second(0, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(3, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, AddWithZeroSecondArgument) {
  rslib::ExtendedFieldElement first(0, ef);
  rslib::ExtendedFieldElement second(3, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(3, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, AddWithAdditiveInverse) {
  // A^2 + A^2 = 0 in GF(8)
  rslib::ExtendedFieldElement first(3, ef);
  rslib::ExtendedFieldElement second(3, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, AdditiveInverse) {
  // A^2 = -A^2 in GF(8)
  rslib::ExtendedFieldElement element(3, ef);
  ASSERT_EQ(-element, element);
}

TEST_F(ExtendedFieldElementFixtureGF8, AdditiveInverseOfZero) {
  // 0 = -0
  rslib::ExtendedFieldElement element(0, ef);
  ASSERT_EQ(-element, element);
}

TEST_F(ExtendedFieldElementFixtureGF9, Add) {
  // A^7 = A + 1 in GF(9)
  rslib::ExtendedFieldElement first(1, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(8, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, AddWithZeroFirstArgument) {
  rslib::ExtendedFieldElement first(0, ef);
  rslib::ExtendedFieldElement second(3, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(3, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, AddWithZeroSecondArgument) {
  rslib::ExtendedFieldElement first(3, ef);
  rslib::ExtendedFieldElement second(0, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(3, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, AddWithAdditiveInverse) {
  // A^4 + 1 = 0 in GF(9)
  rslib::ExtendedFieldElement first(5, ef);
  rslib::ExtendedFieldElement second(1, ef);
  ASSERT_EQ(first + second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, AdditiveInverse) {
  // -A^4 = 1 in GF(9)
  rslib::ExtendedFieldElement element(5, ef);
  ASSERT_EQ(-element, rslib::ExtendedFieldElement(1, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, AdditiveInverseOfZero) {
  // 0 = -0
  rslib::ExtendedFieldElement element(0, ef);
  ASSERT_EQ(-element, element);
}

TEST_F(ExtendedFieldElementFixtureGF8, Subtract) {
  // 1 = A^3 - A in GF(8)
  rslib::ExtendedFieldElement first(4, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first - second, rslib::ExtendedFieldElement(1, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, Subtract) {
  // 1 = A^7 - A in GF(9)
  rslib::ExtendedFieldElement first(8, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first - second, rslib::ExtendedFieldElement(1, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, Multiply) {
  // A^4 = A^3 * A in GF(8)
  rslib::ExtendedFieldElement first(4, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(5, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, MultiplyWithZeroFirstArgument) {
  rslib::ExtendedFieldElement first(0, ef);
  rslib::ExtendedFieldElement second(4, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, MultiplyWithZeroSecondArgument) {
  rslib::ExtendedFieldElement first(4, ef);
  rslib::ExtendedFieldElement second(0, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, Multiply) {
  // A^4 = A^3 * A in GF(9)
  rslib::ExtendedFieldElement first(4, ef);
  rslib::ExtendedFieldElement second(2, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(5, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, MultiplyWithZeroFirstArgument) {
  rslib::ExtendedFieldElement first(0, ef);
  rslib::ExtendedFieldElement second(4, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF9, MultiplyWithZeroSecondArgument) {
  rslib::ExtendedFieldElement first(4, ef);
  rslib::ExtendedFieldElement second(0, ef);
  ASSERT_EQ(first * second, rslib::ExtendedFieldElement(0, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, MultiplicativeInverse) {
  // 1/A^6 = A in GF(8)
  rslib::ExtendedFieldElement element(7, ef);
  ASSERT_EQ(element.multiplicativeInverse(),
            rslib::ExtendedFieldElement(2, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, MultiplicativeInverseOfZero) {
  // There is no multiplicative inverse of zero.
  rslib::ExtendedFieldElement element(0, ef);
  ASSERT_THROW(element.multiplicativeInverse(),
               rslib::ExtendedFieldElementException);
}

TEST_F(ExtendedFieldElementFixtureGF8, MultiplicativeInverseOfOne) {
  // 1/1 = 1
  rslib::ExtendedFieldElement element(1, ef);
  ASSERT_EQ(element.multiplicativeInverse(), element);
}

TEST_F(ExtendedFieldElementFixtureGF9, MultiplicativeInverse) {
  // 1/A^6 = A^2 in GF(9)
  rslib::ExtendedFieldElement element(7, ef);
  ASSERT_EQ(element.multiplicativeInverse(),
            rslib::ExtendedFieldElement(3, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, Divide) {
  // A^4 / A^3 = A in GF(8)
  rslib::ExtendedFieldElement first(5, ef);
  rslib::ExtendedFieldElement second(4, ef);
  ASSERT_EQ(first / second, rslib::ExtendedFieldElement(2, ef));
}

TEST_F(ExtendedFieldElementFixtureGF8, DivideByZero) {
  rslib::ExtendedFieldElement first(5, ef);
  rslib::ExtendedFieldElement second(0, ef);
  ASSERT_THROW(first / second, rslib::ExtendedFieldElementException);
}

TEST_F(ExtendedFieldElementFixtureGF9, Divide) {
  // A^4 / A^3 = A in GF(9)
  rslib::ExtendedFieldElement first(5, ef);
  rslib::ExtendedFieldElement second(4, ef);
  ASSERT_EQ(first / second, rslib::ExtendedFieldElement(2, ef));
}

