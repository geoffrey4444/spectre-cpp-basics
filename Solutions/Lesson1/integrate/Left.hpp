// Distributed under the MIT License.
// See LICENSE.txt for details.

/// Integrate function `func` using the left point rule, using constant spacing
/// `dx` and limits `a` and `b`
double left(double (*const func)(double), double dx,
            double a, double b) noexcept;
