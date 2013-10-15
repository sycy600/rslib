// Copyright 2013 sycy600

#ifndef TESTS_FIXTURES_H_
#define TESTS_FIXTURES_H_

#include <rslib/extendedfield.h>
#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <gtest/gtest.h>

class FixtureGF8 : public ::testing::Test {
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

class FixtureGF16 : public ::testing::Test {
 protected:
  // field GF(2)
  rslib::SimpleField sf = rslib::SimpleField(2);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator = rslib::Polynomial<rslib::SimpleFieldElement>({
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(0, sf),
                  rslib::SimpleFieldElement(0, sf),
                  rslib::SimpleFieldElement(1, sf)});

  // field GF(2^4) = GF(16)
  rslib::ExtendedField ef = rslib::ExtendedField(generator);
};

class FixtureGF9 : public ::testing::Test {
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

class FixtureGF49 : public ::testing::Test {
 protected:
  // field GF(7)
  rslib::SimpleField sf = rslib::SimpleField(7);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator = rslib::Polynomial<rslib::SimpleFieldElement>({
                  rslib::SimpleFieldElement(3, sf),
                  rslib::SimpleFieldElement(1, sf),
                  rslib::SimpleFieldElement(1, sf)});

  // field GF(7^2) = GF(49)
  rslib::ExtendedField ef = rslib::ExtendedField(generator);
};

// Create many codewords for given configuration, randomly
// corrupt codewords, correct them and check if information equals
// to decoded information.
void RSTestFactory(unsigned int iterations,
                   unsigned int errorCorrectionCapability,
                   const rslib::ExtendedField& ef,
                   unsigned int maxNumberOfErrors);

#endif  // TESTS_FIXTURES_H_
