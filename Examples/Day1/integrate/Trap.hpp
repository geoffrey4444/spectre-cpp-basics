#include <functional>

/// Integrate function `func` using the trapezoid rule with fixed step `dx`
/// and limits `a` and `b`.
double trap(const std::function<double(double)>& func, double dx, double a,
            double b) noexcept;
