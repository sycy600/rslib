// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <rslib/simplefieldelement.h>
#include <rslib/extendedfield.h>
#include <rslib/extendedfieldelement.h>
#include <gtest/gtest.h>

TEST(ExtendedField, GetGenerator) {
  rslib::SimpleField sf(2);
  rslib::Polynomial<rslib::SimpleFieldElement>
      generator({rslib::SimpleFieldElement(1, sf),
                 rslib::SimpleFieldElement(0, sf),
                 rslib::SimpleFieldElement(1, sf)});
  rslib::ExtendedField ef(generator);
  ASSERT_EQ(ef.getGenerator(), generator);
}
