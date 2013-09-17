// Copyright 2013 sycy600

/// \file polynomial.h Polynomial class.

#ifndef RSLIB_POLYNOMIAL_H_
#define RSLIB_POLYNOMIAL_H_

#include <algorithm>
#include <iterator>
#include <ostream>
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

/// \brief Returns zero element for given type.
template <class T>
T getZero();

/// \brief Polynomial.
template <class T>
class Polynomial {
 public:
  /// \brief Iterator.
  typedef typename std::vector<T>::iterator iterator;

  /// \brief Constant iterator.
  typedef typename std::vector<T>::const_iterator const_iterator;

  /// \brief Constructor.
  /// \param coefficients Coefficients.
  explicit Polynomial(const std::vector<T>& coefficients)
      : coefficients_(coefficients) {
    if (coefficients.size() == 0) {
      throw PolynomialException("Polynomial cannot be empty");
    }
    cleanZeroes();
  }

  /// \brief Constructor.
  Polynomial() {
    coefficients_ = {getZero<T>()};
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
    // If current coefficients container is too small to set new coefficient
    // then make this polynomial bigger by adding zeroes and new coefficient
    // as the last coefficient.
    unsigned int originalDegree = degree();
    if (index > originalDegree) {
      for (unsigned int i = 0; i < index - originalDegree - 1; ++i) {
        coefficients_.push_back(getZero<T>());
      }
      coefficients_.push_back(value);
    } else {
      coefficients_[index] = value;
    }
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
    Polynomial<T> result(*this);
    unsigned smallerDegree = std::min(degree(), other.degree());
    // Add coefficients on the common positions.
    for (unsigned int i = 0; i < smallerDegree + 1; ++i) {
      result.coefficients_[i] += other.coefficients_[i];
    }
    // If other polynomial is greater then append its coefficients.
    for (unsigned int i = smallerDegree + 1; i < other.degree() + 1; ++i) {
      result.coefficients_.push_back(other.coefficients_[i]);
    }
    result.cleanZeroes();
    std::swap(result, *this);
    return *this;
  }

  /// \brief Subtract two polynomials.
  Polynomial<T>& operator-=(const Polynomial<T>& other) {
    Polynomial<T> result(*this);
    unsigned smallerDegree = std::min(degree(), other.degree());
    // Subtract coefficients on the common positions.
    for (unsigned int i = 0; i < smallerDegree + 1; ++i) {
      result.coefficients_[i] -= other.coefficients_[i];
    }
    // If other polynomial is greater then append its negative coefficients.
    for (unsigned int i = smallerDegree + 1; i < other.degree() + 1; ++i) {
      result.coefficients_.push_back(-other.coefficients_[i]);
    }
    result.cleanZeroes();
    std::swap(result, *this);
    return *this;
  }

  /// \brief Multiply two polynomials.
  Polynomial<T>& operator*=(const Polynomial<T>& other) {
    unsigned int thisDegree = degree();
    unsigned int otherDegree = other.degree();
    Polynomial<T> result;
    for (unsigned int i = 0; i < thisDegree + 1; ++i) {
      for (unsigned int j = 0; j < otherDegree + 1; ++j) {
        if (i + j > result.degree()) {
          result.setValue(i + j, getValue(i) * other.getValue(j));
        } else {
          result.setValue(i + j,
                          result.getValue(i + j)
                          + getValue(i) * other.getValue(j));
        }
      }
    }
    result.cleanZeroes();
    std::swap(result, *this);
    return *this;
  }

  /// \brief Divide two polynomials.
  Polynomial<T>& operator /=(const Polynomial<T>& divisor) {
    Polynomial<T> result(*this);
    result = divideModulo(*this, divisor).quotient_;
    std::swap(result, *this);
    return *this;
  }

  /// \brief Get rest from polynomial division.
  Polynomial<T>& operator %=(const Polynomial<T>& divisor) {
    Polynomial<T> result(*this);
    result = divideModulo(*this, divisor).rest_;
    std::swap(result, *this);
    return *this;
  }

  /// \brief Iterator pointing at first element.
  iterator begin() {
    return coefficients_.begin();
  }

  /// \brief Iterator pointing at after last element.
  iterator end() {
    return coefficients_.end();
  }

  /// \brief Constant iterator pointing at first element.
  const_iterator begin() const {
    return coefficients_.cbegin();
  }

  /// \brief Constant iterator pointing at after last element.
  const_iterator end() const {
    return coefficients_.cend();
  }

 private:
  std::vector<T> coefficients_;

  struct DivisionModuloResult {
     Polynomial<T> quotient_;
     Polynomial<T> rest_;
  };

  // Remove all leading zeroes from polynomial but not the last.
  void cleanZeroes() {
    while ((getZero<T>() == coefficients_[degree()]) && degree() > 0) {
      coefficients_.erase(coefficients_.end() - 1);
    }
  }

  DivisionModuloResult divideModulo(const Polynomial<T>& dividend,
                                    const Polynomial<T>& divisor) {
    if (divisor == Polynomial<T>()) {
      throw PolynomialException("Cannot divide by 0 polynomial");
    }
    Polynomial<T> quotient;
    Polynomial<T> rest = dividend;
    Polynomial<T> zeroPolynomial = Polynomial<T>();
    while (rest != zeroPolynomial && rest.degree() >= divisor.degree()) {
      T result = rest.getValue(rest.degree())
          / divisor.getValue(divisor.degree());
      quotient.setValue(rest.degree() - divisor.degree(), result);
      Polynomial<T> currentShiftedResult;
      currentShiftedResult.setValue(rest.degree() - divisor.degree(), result);
      rest -= currentShiftedResult * divisor;
    }
    return {quotient, rest};  // NOLINT(readability/braces)
  }
};

/// \brief Print polynomial to output stream.
template <class T>
inline std::ostream& operator <<(std::ostream& os, const Polynomial<T>& poly) {
  os << "[";
  std::copy(poly.begin(), poly.end(), std::ostream_iterator<T>(os, ","));
  os << "]";
  return os;
}

/// \brief Add two polynomials.
template <class T>
inline Polynomial<T> operator+(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result += second;
  return result;
}

/// \brief Subtract two polynomials.
template <class T>
inline Polynomial<T> operator-(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result -= second;
  return result;
}

/// \brief Multiply two polynomials.
template <class T>
inline Polynomial<T> operator*(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result *= second;
  return result;
}

/// \brief Divide two polynomials.
template <class T>
inline Polynomial<T> operator/(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result /= second;
  return result;
}

/// \brief Get rest from polynomial division.
template <class T>
inline Polynomial<T> operator%(const Polynomial<T>& first,
                               const Polynomial<T>& second) {
  Polynomial<T> result(first);
  result %= second;
  return result;
}

/// \brief Check if two polynomials are equal.
template <class T>
inline bool operator==(const Polynomial<T>& first,
                       const Polynomial<T>& second) {
  unsigned int currentDegree = first.degree();
  // Check first if degrees match.
  if (currentDegree != second.degree()) {
    return false;
  }
  // Then check if values of elements are equal.
  for (unsigned int i = 0; i < currentDegree + 1; ++i) {
    if (first.getValue(i) != second.getValue(i)) {
      return false;
    }
  }
  return true;
}

/// \brief Check if two polynomials are not equal.
template <class T>
inline bool operator!=(const Polynomial<T>& first,
                       const Polynomial<T>& second) {
  return !(first == second);
}

}  // namespace rslib

#endif  // RSLIB_POLYNOMIAL_H_
