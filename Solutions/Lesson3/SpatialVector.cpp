#include <array>
#include <cstddef>
#include <iostream>

// Stand-in for spectre's DataVector type
#include <valarray>  // Note: in spectre, never #include valarray
using DataVector = std::valarray<double>;
std::ostream& operator<<(std::ostream& os, const DataVector& vector) {
  os << "[ ";
  for (auto element : vector) {
    os << element << " ";
  }
  os << "]";
  return os;
}


namespace Frame {
struct Grid {};
struct Inertial {};
}  // namespace Frame

template <size_t VolumeDim, typename DataType, typename Fr = Frame::Inertial>
class SpatialVector {
 public:
  static constexpr size_t volume_dim = VolumeDim;
  using data_type = DataType;

  SpatialVector(const std::array<DataType, VolumeDim>& data) noexcept
      : data_{data} {}

  // Get a component, with run-time index checking
  DataType get(const size_t i) const noexcept {
    if (i < VolumeDim and i >= 0) {
      return data_[i];
    } else {
      std::cout << "ERROR: SpatialVector index " << i
                << " should be nonnegative and less than " << VolumeDim << "\n";
      exit(-1);
    }
  }

 private:
  std::array<DataType, VolumeDim> data_;
};

// Get a SpatialVector component, with compile-time index checking
template <size_t Index, typename T>
constexpr auto get(const T& vector) noexcept -> typename T::data_type {
  static_assert(Index >= 0 and Index < T::volume_dim,
                "Index should be nonnegative and less than VolumeDim");
  return vector.get(Index);
}

// Euclidean dot product of two spatial vectors
template <size_t VolumeDim, typename DataType, typename Fr>
DataType dot_product(
    const SpatialVector<VolumeDim, DataType, Fr>& vector_a,
    const SpatialVector<VolumeDim, DataType, Fr>& vector_b) noexcept {
  // Initialize to object of same type as vector_a's components, but with value
  // of zero
  DataType result = 0.0 * get<0>(vector_a);
  for (size_t i = 0; i < VolumeDim; ++i) {
    result += vector_a.get(i) * vector_b.get(i);
  }
  return result;
}

int main() {
  SpatialVector<3, double, Frame::Grid> vector{{{1.1, 2.2, 3.3}}};
  std::cout << vector.get(2) << "\n";   // prints 3.3
  std::cout << get<1>(vector) << "\n";  // prints 2.2

  // runtime error: index out of bounds
  // std::cout << vector.get(3) << "\n";

  // compiler error: index out of bounds
  // std::cout << get<3>(vector) << "\n";

  SpatialVector<2, double, Frame::Inertial> a{{{1.0, 2.0}}};
  SpatialVector<2, double, Frame::Inertial> b{{{-1.0, 2.0}}};
  std::cout << dot_product(a, b) << "\n";

  // compiler error: conflicting types for template parameter Fr
  // std::cout << dot_product(a, vector) << "\n";

  SpatialVector<2, DataVector, Frame::Grid> c{
      {{{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}}}};
  std::cout << dot_product(c, c) << "\n";

  return 0;
}
