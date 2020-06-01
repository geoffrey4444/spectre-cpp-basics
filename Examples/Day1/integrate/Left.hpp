#include <functional>

/// Integrate function `func` using the left point rule, using constant spacing
/// `dx` and limits `a` and `b`
double left(const std::function<double(double)>& func, double dx,
            double a, double b) noexcept;
