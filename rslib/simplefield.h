// Copyright 2013 sycy600

/// \file simplefield.h Simple finite field.

#ifndef RSLIB_SIMPLEFIELD_H_
#define RSLIB_SIMPLEFIELD_H_

#include <rslib/simplefieldelement.h>

namespace rslib {

class SimpleFieldElement;

/// \brief Simple finite field.
class SimpleField {
 public:
  /// \brief Constructor.
  explicit SimpleField(unsigned int characteristic)
    : characteristic_(characteristic) { }

  /// \brief Get characteristic.
  unsigned int getCharacteristic() const {
    return characteristic_;
  }

 private:
  const unsigned int characteristic_;

  SimpleFieldElement add(const SimpleFieldElement& first,
                         const SimpleFieldElement& second) const;

  SimpleFieldElement additiveInverse(const SimpleFieldElement& element) const;

  SimpleFieldElement multiply(const SimpleFieldElement& first,
                              const SimpleFieldElement& second) const;

  SimpleFieldElement multiplicativeInverse(
      const SimpleFieldElement& element) const;

  friend class SimpleFieldElement;
};

/// \brief Check if two simple fields are equal.
inline bool operator==(const SimpleField& first,
                       const SimpleField& second) {
  return first.getCharacteristic() == second.getCharacteristic();
}

/// \brief Check if two simple fields are not equal.
inline bool operator!=(const SimpleField& first,
                       const SimpleField& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_SIMPLEFIELD_H_
