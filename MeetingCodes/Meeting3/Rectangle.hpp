#pragma once

class Rectangle {
 public:
  Rectangle(const double width, const double height)
      : width_{width}, height_(height) {}

  static int number_of_sides() { return 4; }

  double perimeter() const;

  double width() const { return width_; }
  double height() const { return height_; }

  double evil_perimeter() const;

 private:
  double width_;
  double height_;
};
