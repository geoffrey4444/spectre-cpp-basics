#include <chrono>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

// Uses the lvalue version of the constructor;
// rvalue argument demands that the vector be passed in using a `std::move`
std::vector<int> scale_scalar_field_1(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(field); // no copy on return
}

// This one is very bad style but technically ok from a language perspective.
// It insists on being called with a `std::move`, and the return is a reference
// to the memory address of the object in the argument of `std::move`, which has
// been scaled in-place
// it performs a copy on the return if assigned to a newly constructed object in
// the calling function, but no copy if assigned to a reference.
std::vector<int>& scale_scalar_field_2(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}

// This one is flexible - can be either called with a `std::move` or not,
// and performs a copy on entry if not, otherwise performs no copy (return value
// elision).
std::vector<int> scale_scalar_field_3(
    std::vector<int> field,  // copy if not called with `std::move`
    const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}

/*
// This will fail to compile: cannot modify the const reference
std::vector<int> bad_scale_scalar_field_1(const std::vector<int>& field,
                                          const double scale_factor) noexcept {
  std::vector<int> local_field = field;
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return local_field;
}
*/

// OK, but probably not what we'd want - it modifies the passed object in-place,
// but then copies on the return
std::vector<int> scale_scalar_field_4(std::vector<int>& field,
                                      const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}

/*
// Doesn't compile - when we return the `field`, it becomes an lvalue.
std::vector<int>&& bad_scale_scalar_field_2(std::vector<int>&& field,
                                            const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}
*/

// OK - acts the same as rvalue in and lvalue out, but cannot be called with a
// `std::move`, so has clearer meaning. It modifies the object passed in and
// returns the reference to the same object (again, copying if assigned to a
// newly constructed object and not if assigned to a reference)
std::vector<int>& scale_scalar_field_5(std::vector<int>& field,
                                      const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}

// This one (curiously) can only be called with the `std::move`, but because the
// rvalue is only a label and does not (directly) imply deep language
// functionality (in current C++ standards), this will (like
// scale_scalar_field_4) perform a copy when returning.
std::vector<int> scale_scalar_field_6(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return field;
}

// This one again works from a language perspective but is arguably even worse
// style than the previous 'bad style' version -- this cannot be called with a
// `std::move`, takes the object by reference, but then leaves the original
// object with potentially garbage values by `std::move`-ing the return. But I
// guess it never copies (yay?).
std::vector<int>&& scale_scalar_field_7(std::vector<int>& field,
                                        const double scale_factor) noexcept {
  for (auto it = field.begin(); it != field.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(field);
}

// now a few that use a local variable as an intermediate

// This one will perform a copy on the assignment (because it needs to get the
// data into the local memory somehow, and the language does not insist on the
// same features on these one-removed rvalue references as if you std::move-d a
// second time)
std::vector<int> scale_scalar_field_8(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  std::vector<int> local_field = field; // surprisingly enough, copies
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return local_field; //no copy
}

std::vector<int> scale_scalar_field_9(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  std::vector<int> local_field = std::move(field);
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return local_field; //no copy
}

// This one will compile, should warn, and results in undefined behavior because
// the reference returned is a reference to the local variable that is freed
// after the return call. Never use this version.
std::vector<int>&& scale_scalar_field_10(std::vector<int>&& field,
                                      const double scale_factor) noexcept {
  std::vector<int> local_field = std::move(field);
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(local_field);
}

// This one actually is okay, because the return value is move-constructed
// before the local reference is destroyed (I think). It's probably best to use
// a different version if you can avoid it because this is unnecessarily
// confusing.
std::vector<int> scale_scalar_field_11(std::vector<int>&& field,
                                       const double scale_factor) noexcept {
  std::vector<int> local_field = std::move(field);
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return std::move(local_field);
}

// works just like the previous one due to the return-value copy elision, no
// copies are made. If you are choosing between this structure and the previous
// one, choose this one.
std::vector<int> scale_scalar_field_12(std::vector<int>&& field,
                                       const double scale_factor) noexcept {
  std::vector<int> local_field = std::move(field);
  for (auto it = local_field.begin(); it != local_field.end(); ++it) {
    *it *= scale_factor;
  }
  return local_field;
}

int main() {
  constexpr size_t size = 1000000;
  constexpr double initial_value = 2.3;
  constexpr double scale_factor = 10.0;
  using clock = std::chrono::high_resolution_clock;
  auto start_time = clock::now();
  auto stop_time = clock::now();

  std::cout << "Initializing scalar field of size " << size << "\n";

  std::vector<int> field_a = std::vector<int>(size);
  for(auto& val : field_a) {
    val = initial_value;
  }

  auto try_function_move = [&start_time, &stop_time, &field_a](auto func) {
    auto local_field_a = field_a;
    std::cout << "original address: " << &local_field_a << "\n";
    start_time = clock::now();
    decltype(auto) field_b = func(std::move(local_field_a), scale_factor);

    stop_time = clock::now();
    std::cout << field_b[size / 2] << " ("
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     stop_time - start_time)
                     .count()
              << " microseconds)\n";
    std::cout << "addresses: " << &local_field_a << ", " << &field_b <<"\n";
  };
  auto try_function_not_move = [&start_time, &stop_time, &field_a](auto func) {
    auto local_field_a = field_a;
    std::cout << "original address: " << &local_field_a << "\n";
    start_time = clock::now();
    decltype(auto) field_b = func(local_field_a, scale_factor);

    stop_time = clock::now();
    std::cout << field_b[size / 2] << " ("
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     stop_time - start_time)
                     .count()
              << " microseconds)\n";
    std::cout << "addresses: " << &local_field_a << ", " << &field_b << "\n";
  };

  try_function_move(&scale_scalar_field_1); // no copies
  try_function_move(&scale_scalar_field_2); // no copies
  try_function_move(&scale_scalar_field_3); // no copies
  try_function_not_move(&scale_scalar_field_3); // one copy
  try_function_not_move(&scale_scalar_field_4); // one copy
  try_function_not_move(&scale_scalar_field_5); // no copies
  try_function_move(&scale_scalar_field_6); // one copy
  try_function_not_move(&scale_scalar_field_7); // no copies

  std::cout << "with locals:\n";
  try_function_move(&scale_scalar_field_8); // one copy
  try_function_move(&scale_scalar_field_9); // no copies
  try_function_move(&scale_scalar_field_11); // no copies
  try_function_move(&scale_scalar_field_12); // no copies
  try_function_move(&scale_scalar_field_10); // no copies, probably segfault

  return 0;
}
