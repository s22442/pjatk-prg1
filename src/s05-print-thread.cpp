
#include <iostream>
#include <string>
#include <thread>

auto print_string(std::string text) -> void
{
    std::cout << text << '\n';
}

auto main() -> int
{
    for (auto i = 0; i < 42; i++) {
        auto text = std::string{"Hello, " + std::to_string(i) + "!"};

        auto print_hello = std::thread{print_string, std::move(text)};
        print_hello.detach();
    }

    return 0;
}
