#include <iostream>
#include <string>

int main() {
  double x = 4.4;
  // int y{4.4}; // nope... {} initialization errors on narrowing conversions
  int y{4};
  
  int z = static_cast<int>(x) + y;

  std::string message = "Hello";

  std::string message_with_number = message + std::to_string(x);

  std::cout << z << "\n";

  std::cout << "Hello world\n";
  return 0;
}
