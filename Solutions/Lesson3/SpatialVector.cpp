#include <array>
#include <cstddef>
#include <iostream>

// Stand-in for spectre's DataVector type
#include <valarray>  // Note: in spectre, never #include valarray
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
  const auto& get(const size_t i) const noexcept {
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
const auto& get(const T& vector) noexcept {
  static_assert(Index >= 0 and Index < T::volume_dim,
                "Index should be nonnegative and less than VolumeDim");
  return vector.get(Index);
}

// Euclidean dot product of two spatial vectors
template <size_t VolumeDim, typename DataType, typename Fr>
DataType dot_product(
    const SpatialVector<VolumeDim, DataType, Fr>& vector_a,
    const SpatialVector<VolumeDim, DataType, Fr>& vector_b) noexcept {
  // Instead of initializing to zero and resetting, save time by assigning to
  // the first term in the sum
  DataType result{get<0>(vetor_a) * get<0>(vector_b)};
  for (size_t i = 1; i < VolumeDim; ++i) {
    result += vector_a.get(i) * vector_b.get(i);
  }
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
