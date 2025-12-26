// By Jurriaan Schreuder

// Compile with:
// g++ main.cpp --std=c++2c -o app

#include <print>
#include <filesystem>
#include <fstream>
#include <expected>
#include <string>
#include <string_view>
#include <vector>


struct MyObj{
    std::filesystem::path    file_path;
    std::ofstream            file;          // file handle, release after use!
                                            
    // std::vector manages memory
    // std::vector<T> is just a pointer, size, capacity
    // all the memory management happens at comp-time, so use freely :)
    std::vector<std::string> written_lines; 

    MyObj(const std::filesystem::path& file_path) : file_path(file_path){
      std::println("MyObj created");
    }

    ~MyObj(){ // called when going out of { scope }
      file.close();
      std::println("MyObj destructed");
    }

    std::expected<void, std::string> open_file() {
      file.open(file_path, std::ios::app);
      if (!file.is_open()){ return std::unexpected("Could not open file"); }
      return {};
    }

    // append line
    std::expected<void, std::string> 
      append_line(const std::string_view& line) // string_view is non-owning
    {
      if(!file.is_open()){ return std::unexpected("File is not opened, cannot append."); }
      // write to file
      file << std::format("{}\n", line);

      // owning copy is made and put in the vector without temporary object (emplace)
      written_lines.emplace_back(line);
      return {};
    }
};

std::size_t count_letters(const std::string& str){
  std::size_t n{0};
  for(const auto& letter : str){ n++; }
  return n;
}

int main(){
  // my new scope
  {
    auto my_obj = MyObj{"funny-quotes.log"};
    if(auto ok = my_obj.open_file()){
      my_obj.append_line("We're giving my object some things to own..");
      my_obj.append_line("Some memory as an array of strings, and a file handle.");
      my_obj.append_line("But fear not the std::vector and the ~destructor will handle this!");
      
      // but now I want to use the pointer and not an 'expensive' copy
      for(const std::string& line : my_obj.written_lines){ // we use a const reference (const type& value)
        std::println("Letters: {}", count_letters(line));
      }

    }else{ std::println("Something went wrong: {}", ok.error()); }
  } // here we're going out of scope so all the memory and file handles are collected
 
  std::println("We're out of the scope, cannot use my_obj anymore");
  std::println("And can also not use references to the strings in my_obj anymore");
}

// $ g++ main.cpp --std=c++2c -o app && ./app
//MyObj created
//Letters: 43
//Letters: 54
//Letters: 66
//MyObj destructed
//We're out of the scope, cannot use my_obj anymore
//And can also not use references to the strings in my_obj anymore

