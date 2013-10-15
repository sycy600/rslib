// Copyright 2013 sycy600

#include <rslib/bmadecoder.h>
#include <rslib/encoder.h>
#include <rslib/extendedfieldelement.h>
#include <rslib/polynomial.h>
#include <tests/fixtures.h>
#include <gtest/gtest.h>
#include <cstdlib>

// Rename these fixtures so Google Test output looks nicer.
class BMADecoderTestFixtureGF16 : public FixtureGF16 {
};

class BMADecoderTestFixtureGF9 : public FixtureGF9 {
};

class BMADecoderTestFixtureGF49 : public FixtureGF49 {
};

TEST_F(BMADecoderTestFixtureGF16, DecodeExampleFourErrors) {
  rslib::Encoder encoder(4, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(7, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(9, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(1, ef),
                  rslib::ExtendedFieldElement(15, ef),
                  rslib::ExtendedFieldElement(10, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(2, rslib::ExtendedFieldElement(13, ef));
  codeword.setValue(5, rslib::ExtendedFieldElement(11, ef));
  codeword.setValue(8, rslib::ExtendedFieldElement(11, ef));
  codeword.setValue(9, rslib::ExtendedFieldElement(12, ef));
  rslib::BMADecoder decoder(4, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF16, DecodeExampleThreeErrors) {
  rslib::Encoder encoder(4, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(9, ef),
                  rslib::ExtendedFieldElement(1, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(5, ef),
                  rslib::ExtendedFieldElement(12, ef),
                  rslib::ExtendedFieldElement(12, ef),
                  rslib::ExtendedFieldElement(4, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(1, rslib::ExtendedFieldElement(14, ef));
  codeword.setValue(5, rslib::ExtendedFieldElement(5, ef));
  codeword.setValue(14, rslib::ExtendedFieldElement(12, ef));
  rslib::BMADecoder decoder(4, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF16, DecodeExampleTwoErrors) {
  rslib::Encoder encoder(4, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(5, ef),
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(10, ef),
                  rslib::ExtendedFieldElement(5, ef),
                  rslib::ExtendedFieldElement(14, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(1, rslib::ExtendedFieldElement(10, ef));
  codeword.setValue(14, rslib::ExtendedFieldElement(0, ef));
  rslib::BMADecoder decoder(4, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF16, DecodeErrorsOnlyOnRedundantPartOfCodeword) {
  rslib::Encoder encoder(4, ef);

  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(9, ef),
                  rslib::ExtendedFieldElement(15, ef),
                  rslib::ExtendedFieldElement(1, ef),
                  rslib::ExtendedFieldElement(12, ef),
                  rslib::ExtendedFieldElement(2, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(11, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(3, rslib::ExtendedFieldElement(6, ef));
  codeword.setValue(5, rslib::ExtendedFieldElement(9, ef));
  codeword.setValue(6, rslib::ExtendedFieldElement(10, ef));
  codeword.setValue(7, rslib::ExtendedFieldElement(4, ef));
  rslib::BMADecoder decoder(4, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF9, DecodeExampleTwoErrors) {
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(2, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(3, rslib::ExtendedFieldElement(2, ef));
  codeword.setValue(5, rslib::ExtendedFieldElement(5, ef));
  rslib::BMADecoder decoder(2, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF9, DecodeExampleOneError) {
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(2, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(5, rslib::ExtendedFieldElement(5, ef));
  rslib::BMADecoder decoder(2, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF9, DecodeExampleNoErrors) {
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(2, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  rslib::BMADecoder decoder(2, ef);
  ASSERT_EQ(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF9, UncorrectableReceivedWord) {
  rslib::Encoder encoder(2, ef);
  rslib::Polynomial<rslib::ExtendedFieldElement> information =
      rslib::Polynomial<rslib::ExtendedFieldElement>({
                  rslib::ExtendedFieldElement(4, ef),
                  rslib::ExtendedFieldElement(3, ef),
                  rslib::ExtendedFieldElement(6, ef),
                  rslib::ExtendedFieldElement(2, ef)});
  rslib::Polynomial<rslib::ExtendedFieldElement> codeword
      = encoder.encode(information);
  codeword.setValue(0, rslib::ExtendedFieldElement(5, ef));
  codeword.setValue(1, rslib::ExtendedFieldElement(5, ef));
  codeword.setValue(5, rslib::ExtendedFieldElement(5, ef));
  rslib::BMADecoder decoder(2, ef);
  ASSERT_NE(decoder.decode(codeword), information);
}

TEST_F(BMADecoderTestFixtureGF16, RSTestFactoryRS15_7) {
  unsigned int errorCorrectionCapability = 4u;
  unsigned int iterations = 100u;
  RSTestFactory(iterations,
                errorCorrectionCapability,
                ef,
                ef.getSize() - 1);
}

TEST_F(BMADecoderTestFixtureGF9, RSTestFactoryRS8_4) {
  unsigned int errorCorrectionCapability = 2u;
  unsigned int iterations = 100u;
  RSTestFactory(iterations,
                errorCorrectionCapability,
                ef,
                ef.getSize() - 1);
}

TEST_F(BMADecoderTestFixtureGF49, RSTestFactoryRS48_38) {
  unsigned int errorCorrectionCapability = 5u;
  unsigned int iterations = 100u;
  RSTestFactory(iterations,
                errorCorrectionCapability,
                ef,
                ef.getSize() - 1);
}

