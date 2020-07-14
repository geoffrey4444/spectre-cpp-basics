- gsl::not_null, gsl::at
- BigScalarField
  - Make a scalar field class, with the field stored as a std::vecto and the size as a member variable
  - Add a resize function to change the size of a scalar field

- Add a free function initialize_grid_scalar_field that initializes a scalar field to a 1D array of integers

- Add a function that (by value) scales the scalar by a double

- Try out the function for a small size (10): create a vector and print the value in the middle (at size / 2)

- Increase the size until it takes 10-20 seconds to run, even with -O3

- Include <chrono>, measure timing

- Replace the scale function with a version that returns by not_null, have the version that returns by value call the non-null version

- change [size / 2] to [size + 40]...undefined behavior
- replace with gsl::at...code terminates
- fix all [] to gsl::at

- add a std::move version of the scale_scalar_field function
- delete the copy construtor and copy assignment, and all uses of it
