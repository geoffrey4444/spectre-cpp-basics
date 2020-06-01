#include <functional>

/// Integrate function `func` using the trapezoid rule with fixed step `dx`
/// and limits `a` and `b`.
double trap(const std::function<double(const double)>& func, const double dx,
            const double a, const double b) noexcept;
