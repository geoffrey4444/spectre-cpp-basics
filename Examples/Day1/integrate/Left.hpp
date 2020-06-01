#include <functional>

/// Integrate function `func` using the left point rule, using constant spacing
/// `dx` and limits `a` and `b`
double left(const std::function<double(const double)>& func, const double dx,
            const double a, const double b) noexcept;
