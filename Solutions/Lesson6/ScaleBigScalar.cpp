#include <chrono>
#include <cstddef>
#include <gsl/gsl>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

class ScalarField {
 public:
  std::vector<double> x{};
  size_t size = 0;

  // constructor
  ScalarField(const size_t& initial_size) noexcept {
    // Resize the vectors, which allocates enough memory to store them all
    x.resize(size);
    size = initial_size;
  }

  void resize(const size_t& new_size) noexcept {
    x.resize(new_size);
    size = new_size;
  }

  // Copy initialize
  // ScalarField(const ScalarField& spatial_vector) noexcept = default;
  ScalarField(const ScalarField& spatial_vector) noexcept = delete;

  // Copy assign
  // ScalarField& operator=(const ScalarField& spatial_vector) noexcept = default;
  ScalarField& operator=(const ScalarField& spatial_vector) noexcept = delete;

  // Move initialize
  ScalarField(ScalarField&& spatial_vector) noexcept = default;

  // Move assign
  ScalarField& operator=(ScalarField&& spatial_vector) noexcept = default;

  // Destructor
  ~ScalarField() = default;
};

void initialize_scalar_field(gsl::not_null<ScalarField*> vector,
                             const size_t size,
                             const double initial_value) noexcept {
  vector->resize(size);
  std::iota(vector->x.begin(), vector->x.end(), initial_value);
}

ScalarField initialize_scalar_field(const size_t size,
                                    const double initial_value) noexcept {
  ScalarField result(size);
  initialize_scalar_field(gsl::make_not_null(&result), size, initial_value);
  return result;
}

void scale_scalar_field(gsl::not_null<ScalarField*> lhs,
                        const double scale_factor) noexcept {
  for (auto it = lhs->x.begin(); it != lhs->x.end(); ++it) {
    *it *= scale_factor;
  }
}

// ScalarField scale_scalar_field(const ScalarField& field,
//                                const double scale_factor) noexcept {
//   ScalarField result = field;
//   scale_scalar_field(gsl::make_not_null(&result), scale_factor);
//   return result;
// }

ScalarField scale_scalar_field(ScalarField&& field,
                               const double scale_factor) noexcept {
  for (auto it = field.x.begin(); it != field.x.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(field);
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  auto stop = std::chrono::high_resolution_clock::now();

  constexpr size_t size = 1000000000;
  constexpr double initial_value = 0.0;
  constexpr double scale_factor = 10.0;

  std::cout << "Creating a scalar field of size " << size << "\n";
  start = std::chrono::high_resolution_clock::now();

  ScalarField field_a = initialize_scalar_field(size, initial_value);
  
  stop = std::chrono::high_resolution_clock::now();
  std::cout << gsl::at(field_a.x, size / 2) << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop -
                                                                     start)
                   .count()
            << " microsec)\n";

  // std::cout << "Scaling a scalar field of size " << size << " by "
  //           << scale_factor << " (by value)\n";
  // start = std::chrono::high_resolution_clock::now();
  //
  // ScalarField field_b = scale_scalar_field(field_a, scale_factor);
  //
  // stop = std::chrono::high_resolution_clock::now();
  // std::cout << gsl::at(field_b.x, size / 2) << " ("
  //           << std::chrono::duration_cast<std::chrono::microseconds>(stop -
  //                                                                    start)
  //                  .count()
  //           << " microsec)\n";

  std::cout << "Scaling a scalar field of size " << size << " by "
            << scale_factor << " (by not_null)\n";
  start = std::chrono::high_resolution_clock::now();

  scale_scalar_field(gsl::make_not_null(&field_a), scale_factor);
  
  stop = std::chrono::high_resolution_clock::now();
  std::cout << gsl::at(field_a.x, size / 2) << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop -
                                                                     start)
                   .count()
            << " microsec)\n";

  std::cout << "Scaling a scalar field of size " << size << " by "
            << scale_factor << " (by std::move)\n";
  start = std::chrono::high_resolution_clock::now();

  ScalarField field_c{
      std::move(scale_scalar_field(std::move(field_a), scale_factor))};

  stop = std::chrono::high_resolution_clock::now();
  std::cout << gsl::at(field_c.x, size / 2) << " ("
            << std::chrono::duration_cast<std::chrono::microseconds>(stop -
                                                                     start)
                   .count()
            << " microsec)\n";

  return 0;
}
