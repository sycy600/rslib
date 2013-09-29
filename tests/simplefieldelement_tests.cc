// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <gtest/gtest.h>
#include <sstream>

class SimpleFieldElementFixtureGF5 : public ::testing::Test {
 protected:
  // field GF(5)
  rslib::SimpleField sf = rslib::SimpleField(5);
};

TEST_F(SimpleFieldElementFixtureGF5,
       ElementWithValueGreaterThanCharacteristic) {
  // The element value is modulo'ed by characteristic so here
  // 5 mod 5 = 0
  rslib::SimpleFieldElement sfe(5, sf);
  ASSERT_EQ(sfe.getValue(), 0u);
}

TEST_F(SimpleFieldElementFixtureGF5, GetValue) {
  rslib::SimpleFieldElement sfe(2, sf);
  ASSERT_EQ(sfe.getValue(), 2u);
}

TEST_F(SimpleFieldElementFixtureGF5, Assign) {
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(3, sf);
  first = second;
  ASSERT_EQ(first.getValue(), 3u);
}

TEST(SimpleFieldElement, AssignToElementFromDifferentField) {
  // If one simple field element is assigned to the second one then they
  // have to be in the same field.
  rslib::SimpleField firstField(5);
  rslib::SimpleFieldElement first(2, firstField);

  rslib::SimpleField secondField(7);
  rslib::SimpleFieldElement second(3, secondField);
  ASSERT_THROW((first = second), rslib::SimpleFieldElementException);
}

TEST_F(SimpleFieldElementFixtureGF5, Add) {
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first + second, rslib::SimpleFieldElement(3, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, AddAndTheResultEqualsToZero) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(3, sf);
  ASSERT_EQ(first + second, rslib::SimpleFieldElement(0, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, AdditiveInverse) {
  rslib::SimpleFieldElement element(4, sf);
  ASSERT_EQ(-element, rslib::SimpleFieldElement(1, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, AdditiveInverseZero) {
  rslib::SimpleFieldElement element(0, sf);
  ASSERT_EQ(-element, rslib::SimpleFieldElement(0, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, Subtract) {
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first - second, rslib::SimpleFieldElement(1, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, SubtractFromZero) {
  rslib::SimpleFieldElement first(0, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first - second, rslib::SimpleFieldElement(4, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, Multiply) {
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(5, sf);
  ASSERT_EQ(first * second, rslib::SimpleFieldElement(0, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, MultiplicativeInverse) {
  rslib::SimpleFieldElement element(3, sf);
  ASSERT_EQ(element.multiplicativeInverse(),
            rslib::SimpleFieldElement(2, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, MultiplicativeInverseOfZero) {
  rslib::SimpleFieldElement element(0, sf);
  ASSERT_THROW(element.multiplicativeInverse(),
               rslib::SimpleFieldElementException);
}

TEST_F(SimpleFieldElementFixtureGF5, Divide) {
  rslib::SimpleFieldElement first(1, sf);
  rslib::SimpleFieldElement second(2, sf);
  ASSERT_EQ(first / second, rslib::SimpleFieldElement(3, sf));
}

TEST_F(SimpleFieldElementFixtureGF5, DivideByZero) {
  rslib::SimpleFieldElement first(1, sf);
  rslib::SimpleFieldElement second(0, sf);
  ASSERT_THROW(first / second, rslib::SimpleFieldElementException);
}

TEST_F(SimpleFieldElementFixtureGF5, Print) {
  rslib::SimpleFieldElement first(3, sf);
  std::ostringstream iss;
  iss << first;
  ASSERT_EQ(iss.str(), "3");
}

