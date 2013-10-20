// Copyright 2013 sycy600

#include <rslib/bma.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>

// Rename these fixtures so Google Test output looks nicer.
class BMATestFixtureGF16 : public FixtureGF16 {
};

class BMATestFixtureGF9 : public FixtureGF9 {
};

TEST_F(BMATestFixtureGF16, FindLFSRPolynomial) {
  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
        rslib::ExtendedFieldElement(13, ef),
        rslib::ExtendedFieldElement(7, ef),
        rslib::ExtendedFieldElement(1, ef),
        rslib::ExtendedFieldElement(12, ef)});

  rslib::Polynomial<rslib::ExtendedFieldElement> LFSRPolynomial
      = rslib::findLFSRPolynomial(syndromes, 2);

  ASSERT_EQ(LFSRPolynomial,
            rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(1, ef),
              rslib::ExtendedFieldElement(10, ef),
              rslib::ExtendedFieldElement(0, ef),
              rslib::ExtendedFieldElement(6, ef)}));
}

TEST_F(BMATestFixtureGF9, FindLFSRPolynomial) {
  rslib::Polynomial<rslib::ExtendedFieldElement> syndromes =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
        rslib::ExtendedFieldElement(8, ef),
        rslib::ExtendedFieldElement(7, ef),
        rslib::ExtendedFieldElement(8, ef),
        rslib::ExtendedFieldElement(3, ef)});

  rslib::Polynomial<rslib::ExtendedFieldElement> LFSRPolynomial
      = rslib::findLFSRPolynomial(syndromes, 2);

  ASSERT_EQ(LFSRPolynomial,
            rslib::Polynomial<rslib::ExtendedFieldElement>({
              rslib::ExtendedFieldElement(1, ef),
              rslib::ExtendedFieldElement(1, ef),
              rslib::ExtendedFieldElement(3, ef)}));
}


