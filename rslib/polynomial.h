// Copyright 2013 sycy600

/// \file polynomial.h Polynomial class.

#ifndef RSLIB_POLYNOMIAL_H_
#define RSLIB_POLYNOMIAL_H_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace rslib {

/// \brief Polynomial exception.
class PolynomialException : public std::runtime_error {
 public:
  /// \brief Constructor.
  explicit PolynomialException(const std::string& message)
     : std::runtime_error(message) {}
};

/// \brief Returns true if element is zero.
/// \param element Number to be compared with zero.
/// \retval true If element is zero.
/// \retval false If element is not zero.
bool isZero(int element) {
  return element == 0;
}

/// \brief Returns true if element is zero.
/// \param element Number to be compared with zero.
/// \retval true If element is zero.
/// \retval false If element is not zero.
bool isZero(double element) {
  return element == 0.0;
}

/// \brief Polynomial.
template <class T>
class Polynomial {
 public:
  /// \brief Constructor.
  /// \param coefficients Coefficients.
  explicit Polynomial(const std::vector<T>& coefficients)
      : coefficients_(coefficients) {
    if (coefficients.size() == 0) {
      throw PolynomialException("Polynomial cannot be empty");
    }
    cleanZeroes();
  }

  /// \brief Return degree of polynomial.
  unsigned int degree() const {
    return coefficients_.size() - 1;
  }

  /// \brief Return coefficient at given index.
  const T& getValue(unsigned int index) const {
    return coefficients_[index];
  }

  /// \brief Set coefficient at given index.
  void setValue(unsigned int index, const T& value) {
    coefficients_[index] = value;
    cleanZeroes();
  }

  /// \brief Evaluate polynomial using Horner's method.
  ///
  /// Example:
  /// Polynomial p(x) = 4x^3 + 3x^2 + 2x + 1 can be rewritten as
  /// p(x) = x*(x*(4*x + 3) + 2) + 1.
  /// For the first case p(x) = 4*x*x*x + 3*x*x + 2*x + 1 there are
  /// 6 multiplications and 3 additions, for the second case there are
  /// 3 multiplications and 3 additions.
  /// \param value Value used to evaluated polynomial.
  /// \return Computed polynomial evaluation.
  T evaluate(const T& value) const {
    unsigned int currentDegree = degree();
    T result = coefficients_[currentDegree];
    for (unsigned int i = 0; i < currentDegree; ++i) {
      result = result * value + getValue(currentDegree - 1 - i);
    }
    return result;
  }

  /// \brief Add two polynomials.
  Polynomial<T>& operator+=(const Polynomial<T>& other) {
    unsigned smallerDegree = std::min(degree(), other.degree());
    // Add coefficients on the common positions.
    for (unsigned int i = 0; i < smallerDegree + 1; ++i) {
      coefficients_[i] += other.coefficients_[i];
    }
    // If other polynomial is greater then append its coefficients.
    for (unsigned int i = smallerDegree + 1; i < other.degree() + 1; ++i) {
      coefficients_.push_back(other.coefficients_[i]);
    }
    cleanZeroes();
    return *this;
  }

 private:
  std::vector<T> coefficients_;

  // Remove all leading zeroes from polynomial but not the last.
  void cleanZeroes() {
    while (isZero(coefficients_[degree()]) && degree() > 0) {
      coefficients_.erase(coefficients_.end() - 1);
    }
  }
};

/// \brief Add two polynomials.
/// \param first First polynomial to add.
/// \param second Second polynomial to add.
/// \return Sum of two polynomials.
template <class T>
inline Polynomial<T> operator+(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result += second;
  return result;
}

/// \brief Check if two polynomials are equal.
/// \param first First operand of equality expression.
/// \param second Second operand of equality expression.
/// \retval true Polynomials are equal.
/// \retval false Polynomials are not equal.
template <class T>
inline bool operator==(const Polynomial<T>& first,
                       const Polynomial<T>& second) {
  unsigned int currentDegree = first.degree();
  // Check first if degrees match.
  if (currentDegree != second.degree()) {
    return false;
  }
  // Then check if values of elements are equal.
  for (unsigned int i = 0; i < currentDegree; ++i) {
    if (first.getValue(i) != second.getValue(i)) {
      return false;
    }
  }
  return true;
}

/// \brief Check if two polynomials are not equal.
/// \param first First operand of equality expression.
/// \param second Second operand of equality expression.
/// \retval true Polynomials are not equal.
/// \retval false Polynomials are equal.
template <class T>
inline bool operator!=(const Polynomial<T>& first,
                       const Polynomial<T>& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_POLYNOMIAL_H_
