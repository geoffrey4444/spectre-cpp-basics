#include <iostream>
#include "brigand.hpp"

namespace tmpl = brigand;

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
  using which_is_smaller = tmpl::if_<tmpl::less<five, four>, three, four>;
  TypeDisplayer<typename which_is_smaller::type> result;

  using unsorted_list = tmpl::list<five, four, three>;
  TypeDisplayer<unsorted_list> unsorted;

  using sorted_list = tmpl::sort<unsorted_list>;
  TypeDisplayer<sorted_list> sorted;

  std::cout << sum::value << "\n";
  return 0;
}
