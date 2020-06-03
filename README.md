# spectre-cpp-basics
Survival guide / crash course on C++ and spectre (https://github.com/sxs-collaboration/spectre)

This repo contains materials originally designed for a survival guide / crash course on C++ programming for SpECTRE I am teaching my undergraduate researchers and others in SXS.

The idea is to introduce some of the C++ that comes up a lot in spectre. For each topic, I thought I’d introduce it in a small, self-contained toy program that we build from the ground up together. 

This is not meant to be an authoritative or complete introduction to these topics. I'm still learning myself, and I'm a physicist, not a C++ professional or a computer scientist. But I hope that these introductions will help my students and other new spectre developers tackle the learning curve a bit more easily.

Prerequisites:
 * I'm assuming that students have basic programming knowledge in any language (e.g. python). Defining variables, if/else, for/while loops, defining your own functions, etc. That said, no topic is too basic to ask about in this course!
 * I'm also assuming that students have some environment where they can compile and run C++-17 programs.
 * The above prerequisites are sufficent for running the toy examples we'll develop. But to apply them to spectre, I also assume students are able to checkout, compile, and run the tests on spectre. Instructions here: (https://spectre-code.org/installation.html)

Here are some topics that I might cover (I will adjust content and pacing depending on how things go):

* Free functions, declaration vs definition, const, constexpr, noexcept
* Classes, structs, and inheritance, including static functions and virtual functions
* Introduce template programming, square(), cube(), and inline and SPECTRE_ALWAYS_INLINE
* Iterators and some basic STL stuff, like std::array and std::vector
* GSL, gsl::at, gsl::not_null, pass by reference & pass by value, signaling nan
* Basic template metaprogramming/Brigand, decltype
* Lambdas
* Variadic programming & parameter packs
* Grab bag: ternary operator, auto, trailing return type, static_cast<>, ...
* Minimizing allocations, move and copy semantics

The content is divided into lessons, but each lesson might take more than one meeting. Solutions prepared in advance for each lesson are in `Solutions/`, while the actual code written during each meeting is in `MeetingCodes/`.
