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


