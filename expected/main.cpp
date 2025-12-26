#include <iostream>
#include <string>
#include <print>
#include <expected>

std::expected<double, std::string> bar(double a, double b) {
    if (b == 0)
        return std::unexpected("Cannot devide by zero!");

    return a / b;
}


int main() {
    auto foo = bar(1, 0);
    if(foo){
        std::println("We found the foo: {foo.value()}");
        std::println("Another way to get to the foo: {*foo}");
    }else{
        std::println("Something wrong at the foo: {foo.error()}");
    }
    // if anything went wrong, give a '0' default value
    double defo = foo.value_or(0);
    std::println("We've the default defo: {defo}");
}
