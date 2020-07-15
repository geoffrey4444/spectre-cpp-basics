#include <chrono>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

class ScalarField {
 public:
  std::vector<double> x{};
  size_t size = 0;

  ScalarField(const size_t initial_size) noexcept {
    x.resize(initial_size);
    size = initial_size;
  }

  void resize(const size_t new_size) noexcept {
    x.resize(new_size);
    size = new_size;
  }
};

ScalarField initialize_scalar_field(const size_t size,
                                    const double initial_value) noexcept {
  ScalarField field{size};
  std::iota(field.x.begin(), field.x.end(), initial_value);
  return field;
}

ScalarField scale_scalar_field(const ScalarField& field,
                               const double scale_factor) noexcept {
  ScalarField result = field;
  for (auto it = result.x.begin(); it != result.x.end(); ++it) {
    *it *= scale_factor;
  }
  return result;
}

ScalarField scale_scalar_field(ScalarField&& field,
const double scale_factor) noexcept {
  for (auto it = field.x.begin(); it != field.x.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(field);
}

int main() {
  constexpr size_t size = 1000000000;
  constexpr double initial_value = 0.0;
  constexpr double scale_factor = 10.0;
  using clock = std::chrono::high_resolution_clock;
  auto start_time = clock::now();
  auto stop_time = clock::now();

  std::cout << "Initializing scalar field of size " << size << "\n";
  start_time = clock::now();

  ScalarField field_a = initialize_scalar_field(size, initial_value);

  stop_time = clock::now();
  std::cout << field_a.x[size / 2] << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop_time -
                                                                     start_time)
                   .count()
            << " microseconds)\n";

  std::cout << "Scaling scalar field by " << scale_factor << "\n";
  start_time = clock::now();

  ScalarField field_b = scale_scalar_field(field_a, scale_factor);

  stop_time = clock::now();
  std::cout << field_b.x[size / 2] << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop_time -
                                                                     start_time)
                   .count()
            << " microseconds)\n";

  std::cout << "(std::move) scaling scalar field by " << scale_factor << "\n";
  start_time = clock::now();

  ScalarField field_c = scale_scalar_field(std::move(field_a), scale_factor);

  stop_time = clock::now();
  std::cout << field_c.x[size / 2] << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop_time -
                                                                     start_time)
                   .count()
            << " microseconds)\n";

  return 0;
}
