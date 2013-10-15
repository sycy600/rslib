// Copyright 2013 sycy600

#include <rslib/errorlocators.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>

// Rename these fixtures so Google Test output looks nicer.
class ErrorLocatorsTestFixtureGF16 : public FixtureGF16 {
};

class ErrorLocatorsTestFixtureGF9 : public FixtureGF9 {
};

TEST_F(ErrorLocatorsTestFixtureGF16, FindErrorLocators) {
  rslib::Polynomial<rslib::ExtendedFieldElement> errorLocatorPolynomial =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
         rslib::ExtendedFieldElement(1, ef),
         rslib::ExtendedFieldElement(10, ef),
         rslib::ExtendedFieldElement(0, ef),
         rslib::ExtendedFieldElement(6, ef)});

  std::vector<rslib::ExtendedFieldElement> LFSRPolynomial
      = rslib::findErrorLocators(errorLocatorPolynomial);

  ASSERT_EQ(LFSRPolynomial,
            std::vector<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(2, ef)}));
}

TEST_F(ErrorLocatorsTestFixtureGF9, FindErrorLocators) {
  rslib::Polynomial<rslib::ExtendedFieldElement> errorLocatorPolynomial
      = rslib::Polynomial<rslib::ExtendedFieldElement>({
          rslib::ExtendedFieldElement(1, ef),
          rslib::ExtendedFieldElement(2, ef)});

  std::vector<rslib::ExtendedFieldElement> LFSRPolynomial
      = rslib::findErrorLocators(errorLocatorPolynomial);

  ASSERT_EQ(LFSRPolynomial,
            std::vector<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(6, ef)}));
}

