#include <array>
#include <cstddef>
#include <iostream>

namespace Frame {
struct Grid {};
struct Inertial {};
}  // namespace Frame

template <typename DataType, size_t VolumeDim, typename Fr>
class SpatialVector {
 public:
  static constexpr size_t volume_dim = VolumeDim;
  using data_type = DataType;

  SpatialVector(const std::array<DataType, VolumeDim>& data) noexcept
      : data_(data) {}

  const auto& get(const size_t i) const noexcept {
    if (i < VolumeDim) {
      return data_[i];
    } else {
      std::cout << "ERROR: index " << i << " out of bounds for VolumeDim "
                << volume_dim << "\n";
      exit(-1);
    }
  }

 private:
  std::array<DataType, VolumeDim> data_;
};

template <size_t Index, typename T>
const auto& get(const T& vector) noexcept {
  static_assert(Index < T::volume_dim,
                "Index should be nonnegative and less than VolumeDim");
  return vector.get(Index);
}

template <typename DataType, size_t VolumeDim, typename Fr>
DataType dot_product(
    const SpatialVector<DataType, VolumeDim, Fr>& vector_a,
    const SpatialVector<DataType, VolumeDim, Fr>& vector_b) noexcept {
  DataType result{get<0>(vector_a) * get<0>(vector_b)};
  for (size_t i = 1; i < VolumeDim; ++i) {
    result += vector_a.get(i) * vector_b.get(i);
  }

  return result;
}

int main() {
  SpatialVector<double, 3, Frame::Inertial> test_spatial_vector{
      {{1.0, 4.0, 9.0}}};
  SpatialVector<double, 3, Frame::Inertial> test_vector_2{{{0.0, 4.0, 0.0}}};

  std::cout << get<1>(test_spatial_vector) << "\n";

  std::cout << dot_product(test_spatial_vector, test_vector_2) << "\n";

  // std::cout << get<444>(test_spatial_vector) << "\n"; // fail at compile_time
  // std::cout << test_spatial_vector.get(444) << "\n"; // fail at runtime

  return 0;
};
