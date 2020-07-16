#include <cstddef>
#include <gsl/gsl>
#include <iostream>
#include <vector>

class BigScalar {
 public:
  std::vector<double> data;  // data for a scalar field

  BigScalar(std::vector<double>& init_vector) noexcept {
    init_vector[4] = 4.4444;
    // vector = std::move(init_vector); // surprise! init_vector destroyed
    data = init_vector;
  }
  // BigScalar(std::vector<double>& init_vector) {
  //   init_vector[4] = 4.4444;
  //   vector = init_vector;
  // }
  BigScalar(std::vector<double>&& init_data) noexcept {
    init_data[4] = 4.4444;
    data = std::move(init_data);
  }
};

BigScalar init_big_scalar(const size_t size) noexcept {
  std::vector<double> test_vector{};
  test_vector.resize(size);
  BigScalar store{std::move(test_vector)};
  // BigScalar store{test_vector};
  // std::cout << test_vector[4] << "\n"; // fails if after
  // std::move(test_vector)
  return store;
}

void multiply_by_constant(gsl::not_null<BigScalar*> scalar,
                          const double factor) noexcept {
  for (auto it = scalar->data.begin(); it != scalar->data.end(); ++it) {
    *it *= factor;
  }
}

int main() {
  constexpr size_t size = 1000000000;
  auto scalar = init_big_scalar(size);
  std::cout << scalar.data[4] << "\n";

  multiply_by_constant(gsl::make_not_null(&scalar), 10.0);
  std::cout << scalar.data[4] << "\n";
  return 0;
}
