#include <iostream>

namespace tmpl {

// Use structs to hold a fixed number of types
struct empty_list {};

template <typename T>
struct list_of_one_type {};

template <typename T1, typename T2>
struct list_of_two_types {};

// Better: a template parameter pack accepts a variable number of types
template <typename... Ts>
struct list {};

// Example of a type that's an integral constant
template <typename T, T Value>
struct integral_constant {
  static const T value = Value;
  using value_type = T;
};

// Example of a type that's a sum of two integral types
template <typename T1, typename T2>
struct plus
    : integral_constant<typename T1::value_type, T1::value + T2::value> {};

// Special case of integral constant: a boolean
template <bool B>
using bool_ = integral_constant<bool, B>;

// Example of a comparison
template <typename T1, typename T2>
struct less : bool_<(T1::value < T2::value)> {};

// Example of an "if" statement:
template <bool B, typename T, typename F>
struct if_ : integral_constant<T::value_type, T::value>;

template <class T, class F>
struct if_<false, T, F> : integral_constant<F::value_type, F::value> {};

}  // namespace tmpl

// Print out the type T at compile time by attempting to instantiate this.
// The attempt will generate a compiler error containing the value
template <typename T>
struct TypeDisplayer;

int main() {
  using test_list = tmpl::list<int, double, char>;

  using three = tmpl::integral_constant<size_t, 3>;
  using four = tmpl::integral_constant<size_t, 4>;
  using five = tmpl::integral_constant<size_t, 5>;

  using list_of_three_integers = tmpl::list<three, four, five>;
  using sum = tmpl::plus<three, four>;

  // Compiler error: prints the LHS and RHS of the sum
  TypeDisplayer<sum> lhs_and_rhs;

  // Compiler error: prints the result of the sum
  TypeDisplayer<tmpl::integral_constant<size_t, sum::value>> lhs_plus_rhs;

  // Compiler error: prints the result of a comparison
  TypeDisplayer<tmpl::bool_<tmpl::less<five, four>::value>> is_less;

  // Compiler error: prints which of two integers is smaller
  using which_is_smaller = tmpl::if_<tmpl::less<five, four>::value, three, four>;
  TypeDisplayer<tmpl::integral_constant<size_t, which_is_smaller::value>> result;

  std::cout << sum::value << "\n";
  return 0;
}