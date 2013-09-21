// Copyright 2013 sycy600

/// \file extendedfield.h Extended finite field.

#ifndef RSLIB_EXTENDEDFIELD_H_
#define RSLIB_EXTENDEDFIELD_H_

#include <rslib/polynomial.h>
#include <rslib/simplefieldelement.h>

namespace rslib {

/// \brief Extended finite field.
class ExtendedField {
 public:
  /// \brief Constructor.
  explicit ExtendedField(const Polynomial<SimpleFieldElement>& generator)
    : generator_(generator) { }

  /// \brief Get generator.
  const Polynomial<SimpleFieldElement>& getGenerator() const {
    return generator_;
  }

 private:
  const Polynomial<SimpleFieldElement> generator_;
};

/// \brief Check if two extended fields are equal.
inline bool operator==(const ExtendedField& first,
                       const ExtendedField& second) {
  return first.getGenerator() == second.getGenerator();
}

/// \brief Check if two extended fields are not equal.
inline bool operator!=(const ExtendedField& first,
                       const ExtendedField& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_EXTENDEDFIELD_H_
