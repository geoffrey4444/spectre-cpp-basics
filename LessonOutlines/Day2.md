## Day 2

- Start with Hello

- Empty square struct

- Length, width variables, print perimeter

- Perimeter function

- Constructor function instead of setting members by hand

- Challenge: make a second rectangle, rect2, and check that the perimeter is correct

- Private length and width

- Struct vs class

- Challenge: add a member function that returns the area

- Add evil_area() that changes the length after computing the area, show how
const member functions prevents this

- Add static const number_of_sides variable and function: same for all rectangles, introduce <cstddef>, size_t

- Challenge: change static variable to static function that takes no arguments and returns the number of sides

- Split into hpp, cpp ... #pragma once to avoid multiple definitions of rect

- Make class square inherit from rectangle (': public Rectangle' after class name), different constructor

- Make new base class polygon with pure virtual functions for area and perimeter

- Make rect inherit from polygon, override virtual functions

- Override keyword: ensures that base class functions are pure virtual. If base class function signatures change, this will catch it, instead of assuming you just added an overload instead

- Challenge: make a RightTriangle class that inherits from Polygon, and print a right triangle's area and perimeter

- Spectre example: MathFunctions





