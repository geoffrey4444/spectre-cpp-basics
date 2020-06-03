// Distributed under the MIT License.
// See LICENSE.txt for details.

#include <cstddef>
#include <iostream>

class Rectangle {
 public:
  Rectangle(const double length, const double width) noexcept
      : length_(length), width_(width) {}

  double perimeter() const noexcept { return 2.0 * (length_ + width_); }
  double area() const noexcept { return length_ * width_; }

  static const size_t number_of_sides() { return 4; }

  // same as area(), but remove the const before noexcept, and the function
  // is allowed to silently change the member variables
  double evil_area() const noexcept {
    const double area = length_ * width_;
    // length_ *= 1.1; // const member functions cannot assign to non-static
    return area;
  }

 private:
  double length_;
  double width_;
};

class Square : public Rectangle {
 public:
  Square(const double length) noexcept : Rectangle(length, length) {}
};

int main() {
  constexpr double length{4.0};
  constexpr double width{3.0};
  Rectangle rect{length, width};

  constexpr double length2 = 7.0;
  constexpr double width2 = 5.0;
  Rectangle rect2{length2, width2};

  std::cout << "Rectangle perimeter: " << rect.perimeter() << "\n";
  std::cout << "Rectangle area take 1: " << rect.area() << "\n";
  std::cout << "Rectangle area take 2: " << rect.evil_area() << "\n";
  std::cout << "Rectangle area take 3: " << rect.area() << "\n";
  // std::cout << "Rect length: " << rect.length_ << "\n"; // length_ private
  std::cout << "Rectangle number of sides: " << rect.number_of_sides() << "\n";

  Square sq{length};
  std::cout << "Square perimeter: " << sq.perimeter() << "\n";

  return 0;
}
