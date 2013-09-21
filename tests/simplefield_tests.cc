// Copyright 2013 sycy600

#include <rslib/polynomial.h>
#include <rslib/simplefield.h>
#include <gtest/gtest.h>

TEST(SimpleField, GetCharacteristic) {
  rslib::SimpleField sf(5);
  ASSERT_EQ(sf.getCharacteristic(), 5u);
}
