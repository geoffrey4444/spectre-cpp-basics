#include <cmath>
#include <iostream>
#include <string>

#include <valarray>  // Note: in spectre, use DataVector; never #include valarray
using DataVector = std::valarray<double>;
std::ostream& operator<<(std::ostream& os, const DataVector& vector) {
  os << "[ ";
  for (auto element : vector) {
    os << element << " ";
  }
  os << "]";
  return os;
}

template <typename T>
struct Complex {
  T real;
  T imag;
};

template <typename T>
T abs(const Complex<T>& x) noexcept {
  return sqrt(x.real * x.real + x.imag * x.imag);
}

// Note: arg() will not convert integral types T to doubles
template <typename T>
T arg(const Complex<T>& x) noexcept {
  return atan2(x.imag, x.real);
}

template <typename T>
Complex<T> operator+(const Complex<T>& lhs, const Complex<T>& rhs) noexcept {
  Complex result{lhs};
  result.real += rhs.real;
  result.imag += rhs.imag;
  return result;
}

template <typename T>
Complex<T> operator-(const Complex<T>& lhs, const Complex<T>& rhs) noexcept {
  Complex result{lhs};
  result.real -= rhs.real;
  result.imag -= rhs.imag;
  return result;
}

template <typename T>
Complex<T> operator*(const double real_factor, const Complex<T>& x) noexcept {
  Complex result{x};
  result.real *= real_factor;
  result.imag *= real_factor;
  return result;
}

template <typename T>
void print(const std::string& label, const Complex<T>& x) noexcept {
  std::cout << label << " = " << x.real << " + " << x.imag << "i"
            << " = " << abs(x) << " exp(" << arg(x) << "i)\n";
}

void print_complex_doubles() noexcept {
  constexpr Complex<double> a{4.0, 3.0};
  constexpr Complex<double> b{1.0, 1.0};

  print("a", a);
  print("b", b);
  print("a + b", a + b);
  print("a - b", a - b);
  print("4a", 4.0 * a);
  print("0a", 0.0 * a);
  print("b - b", b - b);
  std::cout << "\n\n";
}

void print_complex_ints() noexcept {
  constexpr Complex<int> i{4, 3};
  constexpr Complex<int> j{1, 1};

  print("i", i);
  print("j", j);
  print("i + j", i + j);
  std::cout << "\n\n";
}

void print_complex_data_vectors() noexcept {
  const Complex<DataVector> dv_a{ {1.0, 1.0, 3.0}, {0.0, 1.0, 4.0}};
  const Complex<DataVector> dv_b{ {4.0, 4.0, 4.0}, {4.0, 4.0, 4.0}};
  print("dv_a", dv_a);
  print("dv_b", dv_b);
  print("dv_a + dv_b", dv_a + dv_b);
  print("dv_a - dv_a", dv_a - dv_a);
}

int main() {
  print_complex_doubles();
  print_complex_ints();
  print_complex_data_vectors();

  return 0;
}
