// Copyright 2013 sycy600

#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <rslib/syndrome.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>

// Rename these fixtures so Google Test output looks nicer.
class SyndromeTestFixtureGF16 : public FixtureGF16 {
};

class SyndromeTestFixtureGF9 : public FixtureGF9 {
};

TEST_F(SyndromeTestFixtureGF16, CalculateSyndromePolynomial) {
  rslib::Polynomial<rslib::ExtendedFieldElement> receivedWord =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(7, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(9, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(15, ef),
                  rslib::ExtendedFieldElement(10, ef)});

  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes
      = rslib::calculateSyndromePolynomial(receivedWord, 2);

  ASSERT_EQ(syndromes,
            rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(13, ef),
              rslib::ExtendedFieldElement(7, ef),
              rslib::ExtendedFieldElement(1, ef),
              rslib::ExtendedFieldElement(12, ef)}));
}

TEST_F(SyndromeTestFixtureGF9, CalculateSyndromePolynomial) {
  rslib::Polynomial<rslib::ExtendedFieldElement> receivedWord =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(7, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(9, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(15, ef),
                  rslib::ExtendedFieldElement(15, ef),
                  rslib::ExtendedFieldElement(10, ef)});

  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes
      = rslib::calculateSyndromePolynomial(receivedWord, 2);

  ASSERT_EQ(syndromes,
            rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(7, ef),
              rslib::ExtendedFieldElement(8, ef),
              rslib::ExtendedFieldElement(3, ef)}));
}


