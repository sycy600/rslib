// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <gtest/gtest.h>

class ExtendedFieldElementFixture : public ::testing::Test {
 protected:
  rslib::SimpleField sf = rslib::SimpleField(2);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator = rslib::Polynomial<rslib::SimpleFieldElement>({
                 rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(0, sf),
                 rslib::SimpleFieldElement(1, sf)});
  rslib::ExtendedField ef = rslib::ExtendedField(generator);
};

TEST_F(ExtendedFieldElementFixture, PolynomialOfExtendedFieldElements) {
  rslib::Polynomial<rslib::ExtendedFieldElement>
      poly({rslib::ExtendedFieldElement(1, ef),
            rslib::ExtendedFieldElement(0, ef),
            rslib::ExtendedFieldElement(1, ef)});
  ASSERT_EQ(poly.degree(), 2u);
}

TEST_F(ExtendedFieldElementFixture, GetValue) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getValue(), 1u);
}

TEST_F(ExtendedFieldElementFixture, GetField) {
  rslib::ExtendedFieldElement efe(1, ef);
  ASSERT_EQ(efe.getField(), ef);
}

TEST_F(ExtendedFieldElementFixture, Assignment) {
  rslib::ExtendedFieldElement first(1, ef);
  rslib::ExtendedFieldElement second(2, ef);
  first = second;
  ASSERT_EQ(first.getValue(), 2u);
}

TEST_F(ExtendedFieldElementFixture, AssignmentToElementFromDifferentField) {
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
