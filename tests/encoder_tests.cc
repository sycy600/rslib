// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/encoder.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>

// Rename these fixtures so Google Test output looks nicer.
class EncoderFixtureGF8 : public FixtureGF8 {
};

class EncoderFixtureGF9 : public FixtureGF9 {
};

TEST_F(EncoderFixtureGF8, GetCodeGenerator) {
  // error correction capability equals to 2
  // coderword length is 7, because size(GF(8)) - 1 = 7
  // number of redundant elements is 4, because 2*error correction capability=4
  // so number of information elements is 3,
  // because coderword length - number of redundant elements=3
  // and this is code RS(7,3)
  // code generator is x^4 + A^3x^3 + x^2 + Ax + A^3
  rslib::Encoder encoder(2, ef);
  ASSERT_EQ(encoder.getCodeGenerator(),
            rslib::Polynomial<rslib::ExtendedFieldElement>(
              {rslib::ExtendedFieldElement(4, ef),
               rslib::ExtendedFieldElement(2, ef),
               rslib::ExtendedFieldElement(1, ef),
               rslib::ExtendedFieldElement(4, ef),
               rslib::ExtendedFieldElement(1, ef)}));
}

TEST_F(EncoderFixtureGF8, Encode) {
  // information polynomial is x^2 + A^2x + A
  // codeword is x^6 + A^2x^5 + Ax^4 + A^4x^3 + A^5x^2 + A^3
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(2, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(1, ef)});
  ASSERT_EQ(encoder.encode(information),
            rslib::Polynomial<rslib::ExtendedFieldElement>(
              {rslib::ExtendedFieldElement(4, ef),
               rslib::ExtendedFieldElement(0, ef),
               rslib::ExtendedFieldElement(6, ef),
               rslib::ExtendedFieldElement(5, ef),
               rslib::ExtendedFieldElement(2, ef),
               rslib::ExtendedFieldElement(3, ef),
               rslib::ExtendedFieldElement(1, ef)}));
}

TEST_F(EncoderFixtureGF9, GetCodeGenerator) {
  // error correction capability equals to 2
  // coderword length is 8, because size(GF(9)) - 1 = 8
  // number of redundant elements is 4, because 2*error correction capability=4
  // so number of information elements is 4,
  // because coderword length - number of redundant elements=4
  // and this is code RS(8,4)
  // code generator is x^4 + A^7x^3 + A^4x^2 + Ax + A^2
  rslib::Encoder encoder(2, ef);
  ASSERT_EQ(encoder.getCodeGenerator(),
            rslib::Polynomial<rslib::ExtendedFieldElement>(
              {rslib::ExtendedFieldElement(3, ef),
               rslib::ExtendedFieldElement(2, ef),
               rslib::ExtendedFieldElement(5, ef),
               rslib::ExtendedFieldElement(8, ef),
               rslib::ExtendedFieldElement(1, ef)}));
}

TEST_F(EncoderFixtureGF9, Encode) {
  // information polynomial is x^3 + x^2 + A^2x + A
  // codeword is x^7 + x^6 + A^2x^5 + Ax^4 + Ax^3 + A^4x^2 + A^4
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(2, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(1, ef),
                  rslib::ExtendedFieldElement(1, ef)});
  ASSERT_EQ(encoder.encode(information),
            rslib::Polynomial<rslib::ExtendedFieldElement>(
              {rslib::ExtendedFieldElement(5, ef),
               rslib::ExtendedFieldElement(0, ef),
               rslib::ExtendedFieldElement(5, ef),
               rslib::ExtendedFieldElement(2, ef),
               rslib::ExtendedFieldElement(2, ef),
               rslib::ExtendedFieldElement(3, ef),
               rslib::ExtendedFieldElement(1, ef),
               rslib::ExtendedFieldElement(1, ef)}));
}
