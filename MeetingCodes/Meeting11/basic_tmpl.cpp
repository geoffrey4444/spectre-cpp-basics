#include <iostream>

namespace tmpl {
template <typename... Ts>
struct list {};

template <typename T, T Value>
struct integral_constant {
  static const T value = Value;  // tmpl::integral_constant<int, 4>::value is 4
  using value_type = T;  // allows tmpl::integral_constant<int, 4>::type is int
};

template <bool B>
struct bool_ : integral_constant<bool, B> {};

template <typename LHS, typename RHS>
struct less : bool_<(LHS::value < RHS::value)> {};

template <typename LHS, typename RHS>
struct plus
    : integral_constant<typename LHS::value_type, LHS::value + RHS::value> {};

template <bool B, typename T, typename F>
struct if_ : integral_constant<typename T::value_type, T::value> {};

template <typename T, typename F>
struct if_<false, T, F> : integral_constant<typename T::value_type, F::value> {
};
}  // namespace tmpl

template <typename T>
struct TypeDisplayer;

int main() {
  using test = tmpl::list<double, int, char>;

  using three = tmpl::integral_constant<int, 3>;
  using four = tmpl::integral_constant<int, 4>;
  using five = tmpl::integral_constant<int, 5>;

  using sum = tmpl::plus<three, four>;
  using result = tmpl::integral_constant<typename sum::value_type, sum::value>;

  using which_is_smaller =
      tmpl::if_<tmpl::less<three, four>::value, three, four>;

  TypeDisplayer<tmpl::bool_<tmpl::less<four, three>::value>> print_bool;

  TypeDisplayer<
      tmpl::integral_constant<int, which_is_smaller::value>>
      print_if;

  return 0;
}
