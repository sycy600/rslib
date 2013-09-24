// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <gtest/gtest.h>

TEST(SimpleFieldElement, ElementWithValueGreaterThanCharacteristic) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement sfe(5, sf);
  ASSERT_EQ(sfe.getValue(), 0u);
}

TEST(SimpleFieldElement, GetValue) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement sfe(2, sf);
  ASSERT_EQ(sfe.getValue(), 2u);
}

TEST(SimpleFieldElement, Assignment) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(3, sf);
  first = second;
  ASSERT_EQ(first.getValue(), 3u);
}

TEST(SimpleFieldElement, AssignmentToElementFromDifferentField) {
  // If one simple field element is assigned to the second one then they
  // have to be in the same field.
  rslib::SimpleField firstField(5);
  rslib::SimpleFieldElement first(2, firstField);

  rslib::SimpleField secondField(7);
  rslib::SimpleFieldElement second(3, secondField);
  ASSERT_THROW((first = second), rslib::SimpleFieldElementException);
}

TEST(SimpleFieldElement, Addition) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first + second, rslib::SimpleFieldElement(3, sf));
}

TEST(SimpleFieldElement, AdditionAndTheResultEqualsToZero) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(3, sf);
  ASSERT_EQ(first + second, rslib::SimpleFieldElement(0, sf));
}

TEST(SimpleFieldElement, AdditiveInverse) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement element(4, sf);
  ASSERT_EQ(-element, rslib::SimpleFieldElement(1, sf));
}

TEST(SimpleFieldElement, AdditiveInverseZero) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement element(0, sf);
  ASSERT_EQ(-element, rslib::SimpleFieldElement(0, sf));
}

TEST(SimpleFieldElement, Subtraction) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first - second, rslib::SimpleFieldElement(1, sf));
}

TEST(SimpleFieldElement, SubtractionFromZero) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(0, sf);
  rslib::SimpleFieldElement second(1, sf);
  ASSERT_EQ(first - second, rslib::SimpleFieldElement(4, sf));
}

TEST(SimpleFieldElement, Multiply) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(2, sf);
  rslib::SimpleFieldElement second(5, sf);
  ASSERT_EQ(first * second, rslib::SimpleFieldElement(0, sf));
}

TEST(SimpleFieldElement, MultiplicativeInverse) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement element(3, sf);
  ASSERT_EQ(element.multiplicativeInverse(), rslib::SimpleFieldElement(2, sf));
}

TEST(SimpleFieldElement, Divide) {
  rslib::SimpleField sf(5);
  rslib::SimpleFieldElement first(1, sf);
  rslib::SimpleFieldElement second(2, sf);
  ASSERT_EQ(first / second, rslib::SimpleFieldElement(3, sf));
}

