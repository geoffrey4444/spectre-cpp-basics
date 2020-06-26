#include "SpatialVector.hpp"

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>

// Stand-in for DataVector
// NOTE: don't do this when programming spectre!
// just use spectre's DataVector
#include <valarray>
using DataVector = std::valarray<double>;

void print_2d_data_vector(const DataVector& vector) {
  size_t points_per_row =
      static_cast<size_t>(sqrt(static_cast<double>(vector.size())));
  std::cout << std::setprecision(4) << std::fixed;
  for (size_t i = 0; i < vector.size(); ++i) {
    if (i % points_per_row == 0) {
      std::cout << "\n";
    }
    if (vector[i] < 0.0) {
    std::cout << vector[i] << " ";
    } else {
      std::cout << " " << vector[i] << " ";
    }
  }
  std::cout << "\n";
}

int main() {
  DataVector axis_coords{{1.0, -1.0, -3.0, -5.0}};
  DataVector axis_coords_2{{4.0, -3.0, -5.0, 5.0}};
  std::array<DataVector, 2> axis_array{{axis_coords, axis_coords_2}};

  SpatialVector<DataVector, 2, Frame::Inertial> vector_1d{axis_array};
  std::cout << to_string(vector_1d) << "\n";

  SpatialVector<double, 3, Frame::Inertial> test_vector{{1.0, 4.0, 9.0}};
  std::cout << get<0>(test_vector) << "\n";

  // A grid calculation
  constexpr size_t volume_dim = 2;
  constexpr size_t points_per_dimension = 9;
  const size_t number_of_points = pow(points_per_dimension, volume_dim);
  constexpr double lower_bound = -4.0;
  constexpr double upper_bound = 4.0;
  constexpr double delta = (upper_bound - lower_bound) /
                           static_cast<double>(points_per_dimension - 1);

  DataVector x_coords(0.0, number_of_points);
  DataVector y_coords(0.0, number_of_points);

  size_t i = 0;
  for (double y = upper_bound; y >= lower_bound; y -= delta) {
    for (double x = lower_bound; x <= upper_bound; x += delta) {
      x_coords[i] = x;
      y_coords[i] = y;
      ++i;
    }
  }

  SpatialVector<DataVector, 2, Frame::Inertial> coords{{x_coords, y_coords}};
  std::cout << to_string(coords) << "\n";

  print_2d_data_vector(y_coords);

  print_2d_data_vector(exp(-0.25 * dot_product(coords, coords)));

  return 0;
}
