// Copyright 2013 sycy600

/// \file simplefield.h Simple finite field.

#ifndef RSLIB_SIMPLEFIELD_H_
#define RSLIB_SIMPLEFIELD_H_

namespace rslib {

/// \brief Simple finite field.
class SimpleField {
 public:
  /// \brief Constructor.
  explicit SimpleField(unsigned int characteristic);

  /// \brief Get characteristic.
  unsigned int getCharacteristic() const;

  /// \brief Check if two simple fields are equal.
  bool operator==(const SimpleField& other) const;

  /// \brief Check if two simple fields are not equal.
  bool operator!=(const SimpleField& other) const;

 private:
  const unsigned int characteristic_;
};

}  // namespace rslib

#endif  // RSLIB_SIMPLEFIELD_H_
