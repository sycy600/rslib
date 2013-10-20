// Copyright 2013 sycy600

#include <rslib/extendedfield.h>
#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <gtest/gtest.h>

TEST(ExtendedField, GetGenerator) {
  rslib::SimpleField sf(2);
  // generator for GF(8), p(x) = x^3 + x + 1
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator({rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(0, sf),
                 rslib::SimpleFieldElement(1, sf)});
  rslib::ExtendedField ef(generator);
  ASSERT_EQ(ef.getGenerator(), generator);
  ASSERT_EQ(ef.getCharacteristic(), 2u);
  ASSERT_EQ(ef.getSize(), 8u);
  ASSERT_EQ(ef.getExtensionOrder(), 3u);
}
