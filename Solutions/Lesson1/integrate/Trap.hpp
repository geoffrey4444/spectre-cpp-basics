// Distributed under the MIT License.
// See LICENSE.txt for details.

/// Integrate function `func` using the trapezoid rule with fixed step `dx`
/// and limits `a` and `b`.
double trap(double (*const func)(double), double dx, double a,
            double b) noexcept;
