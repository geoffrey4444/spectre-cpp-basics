#include <cstddef>
#include <gsl/gsl>
#include <iostream>
#include <limits>
#include <vector>

class BigScalar {
 public:
  std::vector<double> data{};

  BigScalar(gsl::not_null<std::vector<double>*> initial_data,
            const double special_value) {
    (*initial_data)[4] = special_value;
    data = *initial_data;
  }

  BigScalar(std::vector<double>&& initial_data, const double special_value) {
    initial_data[4] = special_value;
    data = std::move(initial_data);
  }

  // ... lots of other features like doing math with scalars
};

// template <size_t Size>
// std::array<double, Size + 1> append_to_array(
//     std::array<double, Size>&& input_array, double new_value) {
//   std::array<double, Size + 1> new_array{};
//   // for loop to fill in the old values
//   for (...) {
//     gsl::at(new_array, i) = gsl::at(old_array, i);
//   }
//   new_array[Size] = new_value;
//   return new_array;
// }

int main() {
  constexpr auto size = 100000;
  constexpr double special_value = 4.0;
  std::vector<double> test_vector{};
  test_vector.resize(size);
  for (double& element : test_vector) {
    element = 5.0;
  }

  // BigScalar big_scalar{gsl::make_not_null(&test_vector), special_value};

  BigScalar big_scalar{std::move(test_vector), special_value};
  // std::cout << test_vector[4] << "\n";

  std::cout << gsl::at(big_scalar.data, size / 2) << "\n";
  std::cout << big_scalar.data[4] << "\n";

  double x = std::numeric_limits<double>::signaling_NaN();
  // x = 7;
  std::cout << x + big_scalar.data[4] << "\n";

  /*
  tnsr::I<double, 3, Frame::Inertial> x;
  tnsr::I<double, 3, Frame::Inertial> y;
  double dot_product = get<0>(x) * get<0>(y);
  */

  return 0;
}
