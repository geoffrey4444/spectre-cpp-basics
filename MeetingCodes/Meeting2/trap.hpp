// Use the trapezoid rule (e.g. wikipedia) to integrate a function of 
// one variable func, using fixed step size `step_size` between limits
// `lower_bound` and `upper_bound`.
double trap(double (*const func)(const double), double step_size,
            double lower_bound, double upper_bound) noexcept;
