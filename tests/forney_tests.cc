// Copyright 2013 sycy600

#include <rslib/extendedfieldelement.h>
#include <rslib/forney.h>
#include <rslib/polynomial.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>
#include <vector>

// Rename these fixtures so Google Test output looks nicer.
class ForneyTestFixtureGF16 : public FixtureGF16 {
};

class ForneyTestFixtureGF9 : public FixtureGF9 {
};

TEST_F(ForneyTestFixtureGF16, FindErrorValues) {
  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes
      = rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(7, ef),
              rslib::ExtendedFieldElement(6, ef),
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(0, ef),
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(6, ef),
              rslib::ExtendedFieldElement(13, ef),
              rslib::ExtendedFieldElement(2, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> errorLocatorPolynomial
      = rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(1, ef),
              rslib::ExtendedFieldElement(14, ef),
              rslib::ExtendedFieldElement(2, ef),
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(10, ef)});
  std::vector<rslib::ExtendedFieldElement> errorLocators
      = std::vector<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(10, ef),
              rslib::ExtendedFieldElement(9, ef),
              rslib::ExtendedFieldElement(6, ef),
              rslib::ExtendedFieldElement(3, ef)});
  std::vector<rslib::ExtendedFieldElement> errorValues
      = rslib::ForneyAlgorithm::findErrorValues(errorLocators,
                                                syndromes,
                                                errorLocatorPolynomial);
  ASSERT_EQ(errorValues,
            std::vector<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(4, ef),
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(5, ef),
              rslib::ExtendedFieldElement(2, ef)}));
}

TEST_F(ForneyTestFixtureGF9, FindErrorValues) {
  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes
      = rslib::Polynomial<rslib::ExtendedFieldElement>({
          rslib::ExtendedFieldElement(5, ef),
          rslib::ExtendedFieldElement(2, ef),
          rslib::ExtendedFieldElement(7, ef),
          rslib::ExtendedFieldElement(4, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> errorLocatorPolynomial
      = rslib::Polynomial<rslib::ExtendedFieldElement>({
          rslib::ExtendedFieldElement(1, ef),
          rslib::ExtendedFieldElement(2, ef)});
  std::vector<rslib::ExtendedFieldElement> errorLocators
      = std::vector<rslib::ExtendedFieldElement>({
          rslib::ExtendedFieldElement(6, ef)});
  std::vector<rslib::ExtendedFieldElement> errorValues
      = rslib::ForneyAlgorithm::findErrorValues(errorLocators,
                                                syndromes,
                                                errorLocatorPolynomial);
  ASSERT_EQ(errorValues,
            std::vector<rslib::ExtendedFieldElement>(
                {rslib::ExtendedFieldElement(8, ef)}));
}
