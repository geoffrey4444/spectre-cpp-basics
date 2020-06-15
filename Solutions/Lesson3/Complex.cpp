// Distributed under the MIT License.
// See LICENSE.txt for details.

// NOTE: this class is just an example of templates, with complex numbers
// serving as a concrete goal for the example. In real production code,
// just use std::complex (#include <complex>), not a home-grown class like this.

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

using std::abs;  // otherwise, call to abs() on native types is
                 // implementation-dependent
using std::to_string;

#include <valarray>  // Note: in spectre, use DataVector; never #include valarray
using DataVector = std::valarray<double>;
std::ostream& operator<<(std::ostream& os, const DataVector& vector) {
  std::string output = "[";
  for (auto element : vector) {
    output += to_string(element) + " ";
  }
  output.pop_back();
  output += "]";

  os << output;
  return os;
}

template <typename T>
struct Complex {
  T real;
  T imag;
};

template <typename T>
auto real(const Complex<T>& x) noexcept {
  return x.real;
}

template <typename T>
auto imag(const Complex<T>& x) noexcept {
  return x.imag;
}

template <typename T>
auto abs(const Complex<T>& x) noexcept {
  return sqrt(x.real * x.real + x.imag * x.imag);
}

// Note: arg() will not convert integral types T to doubles
template <typename T>
auto arg(const Complex<T>& x) noexcept {
  return atan2(x.imag, x.real);
}

template <typename T>
auto operator+(const Complex<T>& lhs, const Complex<T>& rhs) noexcept {
  Complex<T> result{lhs};
  result.real += rhs.real;
  result.imag += rhs.imag;
  return result;
}

template <typename T>
auto operator-(const Complex<T>& lhs, const Complex<T>& rhs) noexcept {
  Complex<T> result{lhs};
  result.real -= rhs.real;
  result.imag -= rhs.imag;
  return result;
}

template <typename T>
auto operator*(const double real_factor, const Complex<T>& x) noexcept {
  Complex<T> result{x};
  result.real *= real_factor;
  result.imag *= real_factor;
  return result;
}

template <typename T>
std::string to_string(const Complex<T>& x) noexcept {
  std::stringstream result;
  result << real(x) << " + " << imag(x) << "i = " << abs(x) << " exp(" << arg(x)
         << "i)\n";
  return result.str();
}

void print_complex_doubles() noexcept {
  constexpr Complex<double> a{4.0, 3.0};
  constexpr Complex<double> b{1.0, 1.0};

  std::cout << to_string(a) << "\n";
  std::cout << to_string(b) << "\n";
  std::cout << to_string(a + b) << "\n";
  std::cout << to_string(a - b) << "\n";
  std::cout << to_string(4.0 * a) << "\n";
  std::cout << to_string(0.0 * a) << "\n";
  std::cout << to_string(b - b) << "\n";
  std::cout << "\n\n";
}

void print_complex_ints() noexcept {
  constexpr Complex<int> i{4, 3};
  constexpr Complex<int> j{1, 1};

  std::cout << to_string(i) << "\n";
  std::cout << to_string(j) << "\n";
  std::cout << to_string(i + j) << "\n";
  std::cout << "\n\n";
}

void print_complex_data_vectors() noexcept {
  const Complex<DataVector> dv_a{{1.0, 1.0, 3.0}, {0.0, 1.0, 4.0}};
  const Complex<DataVector> dv_b{{4.0, 4.0, 4.0}, {4.0, 4.0, 4.0}};
  std::cout << to_string(dv_a) << "\n";
  std::cout << to_string(dv_b) << "\n";
  std::cout << to_string(dv_a + dv_b) << "\n";
  std::cout << to_string(dv_a - dv_a) << "\n";
}

int main() {
  print_complex_doubles();
  print_complex_ints();
  print_complex_data_vectors();

  return 0;
}
