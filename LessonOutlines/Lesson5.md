## Lesson 5
  - Template metaprogramming
    - basic tmpl::list<>
      - structs for lists of zero, 1, 2, ... types
      - '...' and template parameter packs
      - basic integral constant type:
        - first parameter is type of value, second is the value
        - has member static const value and alias value_type for type of value
      - plus : inherits from integral constant, value is the sum
      - challenge: implement other arithmetic operations using tmpl::list and tmpl::integral_constant
      - boolean constant as specialization of int
      - boolen: less
      - challenge: implement other comparison operations
      - bonus example: if_
    - brigand
      - redo the basic example using brigand functions
      - example algorithm: sort integral types
  