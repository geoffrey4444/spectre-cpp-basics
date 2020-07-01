#include <iostream>
#include <tuple>
#include <utility>

template <typename T, size_t Extra>
T sum(const T& lhs, const T& rhs) noexcept {
  return lhs + rhs + static_cast<double>(Extra);
}

namespace Rect {
struct Height {};
struct Width {};
}  // namespace Rect

template <typename T>
double area(const T& box) noexcept {
  return std::get<std::pair<Rect::Width, double>>(box).second *
         std::get<std::pair<Rect::Height, double>>(box).second;
}

int main() {
  // std::tuple example
  std::tuple<std::pair<Rect::Width, double>, std::pair<Rect::Height, double>>
      box{{{}, 4.0}, {{}, 5.0}};

  std::cout << area(box) << "\n";

  std::tuple<std::pair<Rect::Width, double>> oops_box{{{}, 4.0}};
  // std::cout << area(oops_box) << "\n"; // does not compile

  return 0;
}

/*

  SpEC way (runtime keys):

  { key -> value }

  { "Lapse" -> 0.1, "Shift" -> {0.1, 0.2, 0.3}, ... }

  // In SpEC, e.g.
  EvaluateScalarFormula(A = Lapse; Output = sqrt(Lapse);)

  SpECTRE way (compile-time keys):

  { compile-time-key-1 -> value-1, compile-time-key-2 -> value-2 }

*/