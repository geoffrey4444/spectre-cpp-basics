#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>

#include "SpatialVector.hpp"

// Stand-in for DataVector
// NOTE: don't ever include valarray in spectre code; use spectre's DataVector
#include <valarray>
using DataVector = std::valarray<double>;

int main() {
  constexpr size_t volume_dim = 2;
  constexpr size_t points_per_dimension = 9;
  const size_t number_of_points = pow(points_per_dimension, volume_dim);
  constexpr double lower_bound = -4.0;
  constexpr double upper_bound = 4.0;
  constexpr double delta = (upper_bound - lower_bound) /
                           static_cast<double>(points_per_dimension - 1);

  // Note: spectre DataVector constructors take these parameters in
  // the opposite order: first the size, then the value to initialize each
  // element
  DataVector x_coords(std::numeric_limits<double>::signaling_NaN(),
                      number_of_points);
  DataVector y_coords(std::numeric_limits<double>::signaling_NaN(),
                      number_of_points);

  size_t i = 0;
  for (double y = lower_bound; y <= upper_bound; y += delta) {
    for (double x = lower_bound; x <= upper_bound; x += delta) {
      x_coords[i] = x;
      y_coords[i] = y;
      ++i;
    }
  }

  SpatialVector<DataVector, 2, Frame::Inertial> coords{{x_coords, y_coords}};
  std::cout << to_string(coords) << "\n";
  std::cout << to_string(dot_product(coords, coords)) << "\n";

  std::cout << "\n\n";

  std::cout << std::fixed << std::setprecision(4);
  DataVector gauss = exp(-1.0 * dot_product(coords, coords));
  for (size_t i = 0; i < number_of_points; ++i) {
    if (i % points_per_dimension == 0) {
      std::cout << "\n";
    }
    std::cout << gauss[i] << " ";
  }
  std::cout << "\n";

  return 0;
};
