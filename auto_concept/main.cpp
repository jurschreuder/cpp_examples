// By Jurriaan Schreuder

// Compile with:
// g++ main.cpp --std=c++2c -o app

#include <print>

// completely automatic
auto add_1(const auto& a, const auto& b){
  return a+b;
}

// semi-automatic
template <typename T>
concept I = std::integral<T>;

auto add_2(const I auto& a, const I auto& b){
  return a+b;
}

int main(){

  std::size_t a{5};
  std::size_t b{10};
  std::println("add_1 {} + {} = {}", a, b, add_1(a,b));

  std::string c{"Hello"};
  std::string d{"World"};
  std::println("add_1 {} + {} = {}", c, d, add_1(c,d));

  std::println("add_2 {} + {} = {}", a, b, add_2(a,b));

  return 0;
}
