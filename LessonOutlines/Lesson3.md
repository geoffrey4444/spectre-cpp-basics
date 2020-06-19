## Lesson 3

  - Recap: a "square" function templated on type
    - Demonstrate calling for double, int, and manually setting type
    - Make a "double" and "halve" function
  - Using templates: std::array and std::vector demo

  - Challenge: Build a complex struct using doubles for re, im part
    - Add free functions for real, imag, abs, arg, +, -, scale by real factor
    - Challenge: Add functions for *, /
    - Add a print() function that prints complex numbers
    - Template Complex and free functions on type, try with double, int

  - SpatialVector
    - Start with a 3D vector of doubles
      - Constructor
      - runtime get function
      - runtime error for size out of bounds
      - template on type
      - compile-time bounds check for get<>
        - constexpr auto get(), index is template parameter
        - store volume_dim, data_type in class
        - static assert
        - call runtime get (return const auto&)
      - template on dimension
      - tempate on frame
      - Dot 

    - Challenge: implement cross product for SpatialVector, checking dimension is 2 or 3 at compile time
    - Challenge: implement SpacetimeVector
    - Challenge: implement spatial rank-2 tensor

    - Import valarray as a stand-in for DataVector
    - Overload operator<< for valarray
    - Try out complex valarray
    - Challenge: try a large complex DataVector...how big before it gets slow?
    - Bonus challenge: Revisit the integrator from lesson 1. Change f(x) to a templated type instead of a function pointer type, and try passing in a struct that has operator() overloaded inside it


