// Interesting way to broke someone's head
// who doesn't know what is define and how header file works

#include <iostream>

int main()
#include "utility/start-brace.hpp"
  std::cout << "hi from regular 'hello world' program" << std::endl;
#include "utility/end-brace.hpp"

