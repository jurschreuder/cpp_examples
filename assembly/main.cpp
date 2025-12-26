
#include <print>

int main(){

  std::string passw{"secret password"};
  char arr[0];
  char* p = arr;


  for(std::size_t i{0}; i < 20; i++){
    asm volatile ( "add %0, %0, #1" : "+r"(p) );
    std::println("Christmas C/C++ version: {}", static_cast<char>(*p));
  }
}

//   Prints:
//                                     
//   Christmas C/C++ version: s
//   Christmas C/C++ version: e
//   Christmas C/C++ version: c
//   Christmas C/C++ version: r
//   Christmas C/C++ version: e
//   Christmas C/C++ version: t
//   Christmas C/C++ version:
//   Christmas C/C++ version: p
//   Christmas C/C++ version: a
//   Christmas C/C++ version: s
//   Christmas C/C++ version: s
//   Christmas C/C++ version: w
//   Christmas C/C++ version: o
//   Christmas C/C++ version: r
//   Christmas C/C++ version: d
//   Christmas C/C++ version:
//   Christmas C/C++ version:
//   Christmas C/C++ version:
//   Christmas C/C++ version: 8
//   Christmas C/C++ version:


