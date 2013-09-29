// Copyright 2013 sycy600

#include <rslib/zechlogarithm.h>
#include <gtest/gtest.h>
#include <limits>

TEST(ZechLogarithm, Print) {
  rslib::ZechLogarithm zechLogarithm(0);
  std::ostringstream iss;
  iss << zechLogarithm;
  ASSERT_EQ(iss.str(), "0");
}

TEST(ZechLogarithm, PrintMinusInfinity) {
  rslib::ZechLogarithm zechLogarithm(
        std::numeric_limits<unsigned int>::max());
  std::ostringstream iss;
  iss << zechLogarithm;
  ASSERT_EQ(iss.str(), "-INF");
}

TEST(ZechLogarithm, IsMinusInfinity) {
  rslib::ZechLogarithm zechLogarithmMinusInfinity(
        std::numeric_limits<unsigned int>::max());
  ASSERT_TRUE(zechLogarithmMinusInfinity.isMinusInfinity());
  rslib::ZechLogarithm zechLogarithmNotMinusInfinity(1);
  ASSERT_FALSE(zechLogarithmNotMinusInfinity.isMinusInfinity());
}
