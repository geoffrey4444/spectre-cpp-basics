#pragma once

#include <array>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>

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

// to_string() that returns a std::string from a container (e.g. std::array)
template <typename T>
std::string to_string(const T& container) noexcept {
  std::stringstream output_stream{};
  output_stream << "[";
  for (auto element : container) {
    output_stream << element << " ";
  }
  std::string output_string = output_stream.str();
  output_string.pop_back();
  return output_string + "]";
}

// to_string() for SpatialVectors
template <typename DataType, size_t VolumeDim, typename Fr>
std::string to_string(
    const SpatialVector<DataType, VolumeDim, Fr>& spatial_vector) noexcept {
  std::stringstream output_stream{};
  output_stream << "[";
  for (size_t i = 0; i < VolumeDim; ++i) {
    output_stream << to_string(spatial_vector.get(i)) << " ";
  }
  std::string output_string = output_stream.str();
  output_string.pop_back();
  return output_string + "]";
}
