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
  ASSERT_EQ(poly.degree(), 2u);
}

TEST_F(ExtendedFieldElementFixtureGF8, GetValue) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getValue(), 1u);
}

TEST_F(ExtendedFieldElementFixtureGF8, GetField) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getField(), ef);
}

TEST_F(ExtendedFieldElementFixtureGF8, Assignment) {
  rslib::ExtendedFieldElement first(1, ef);
  rslib::ExtendedFieldElement second(2, ef);
  first = second;
  ASSERT_EQ(first.getValue(), 2u);
}

TEST_F(ExtendedFieldElementFixtureGF8, AssignmentToElementFromDifferentField) {
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

TEST_F(ExtendedFieldElementFixtureGF8, PolynomialRepresentationGF2x) {
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

TEST_F(ExtendedFieldElementFixtureGF9, PolynomialRepresentationGF3x) {
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
            rslib::ExtendedField::ZechLogarithm(0));
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(
              std::numeric_limits<unsigned int>::max()));
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(3));
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(6));
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(1));
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(5));
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(4));
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(2));
}

TEST_F(ExtendedFieldElementFixtureGF9, ZechLogarithms) {
  ASSERT_EQ(rslib::ExtendedFieldElement(0, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(0));
  ASSERT_EQ(rslib::ExtendedFieldElement(1, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(8));
  ASSERT_EQ(rslib::ExtendedFieldElement(2, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(7));
  ASSERT_EQ(rslib::ExtendedFieldElement(3, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(3));
  ASSERT_EQ(rslib::ExtendedFieldElement(4, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(5));
  ASSERT_EQ(rslib::ExtendedFieldElement(5, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(
              std::numeric_limits<unsigned int>::max()));
  ASSERT_EQ(rslib::ExtendedFieldElement(6, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(2));
  ASSERT_EQ(rslib::ExtendedFieldElement(7, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(1));
  ASSERT_EQ(rslib::ExtendedFieldElement(8, ef).getZechLogarithm(),
            rslib::ExtendedField::ZechLogarithm(6));
}

TEST_F(ExtendedFieldElementFixtureGF8, ZechLogarithmsPrint) {
  rslib::ExtendedField::ZechLogarithm zechLogarithm
      = rslib::ExtendedFieldElement(0, ef).getZechLogarithm();
  std::ostringstream iss;
  iss << zechLogarithm;
  ASSERT_EQ(iss.str(), "0");
}

TEST_F(ExtendedFieldElementFixtureGF8, ZechLogarithmsPrintMinusInfinity) {
  rslib::ExtendedField::ZechLogarithm zechLogarithm
      = rslib::ExtendedFieldElement(1, ef).getZechLogarithm();
  std::ostringstream iss;
  iss << zechLogarithm;
  ASSERT_EQ(iss.str(), "-INF");
}

TEST_F(ExtendedFieldElementFixtureGF8, ZechLogarithmsIsMinusInfinity) {
  rslib::ExtendedField::ZechLogarithm zechLogarithmMinusInfinity
      = rslib::ExtendedFieldElement(1, ef).getZechLogarithm();
  ASSERT_TRUE(zechLogarithmMinusInfinity.isMinusInfinity());
  rslib::ExtendedField::ZechLogarithm zechLogarithmNotMinusInfinity
      = rslib::ExtendedFieldElement(0, ef).getZechLogarithm();
  ASSERT_FALSE(zechLogarithmNotMinusInfinity.isMinusInfinity());
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
