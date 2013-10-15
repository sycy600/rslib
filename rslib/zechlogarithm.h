// Copyright 2013 sycy600

/// \file zechlogarithm.h Zech logarithm class.

#ifndef RSLIB_ZECHLOGARITHM_H_
#define RSLIB_ZECHLOGARITHM_H_

#include <ostream>

namespace rslib {

/// \brief Zech Logarithm class.
class ZechLogarithm {
 public:
  /// \brief Constructor.
  explicit ZechLogarithm(unsigned int value);

  /// \brief Check if Zech Logarithm equals to minus infinity.
  bool isMinusInfinity() const;

  /// \brief Get value.
  unsigned int getValue() const;

  /// \brief Check if two Zech logarithms are equal.
  bool operator==(const ZechLogarithm& other) const;

  /// \brief Check if two Zech logarithms are not equal.
  bool operator!=(const ZechLogarithm& other) const;

 private:
  unsigned int value_;
};

/// \brief Print Zech logarithm to output stream.
inline std::ostream& operator<<(
    std::ostream& os,  // NOLINT(runtime/references)
    const ZechLogarithm& zechLogarithm) {
  if (zechLogarithm.isMinusInfinity()) {
    os << "-INF";
  } else {
    os << zechLogarithm.getValue();
  }
  return os;
}

}  // namespace rslib

#endif  // RSLIB_ZECHLOGARITHM_H_
