
#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }

    auto const pwd = std::string{argv[1]};

    auto new_pwd = std::string{};

    while (pwd != new_pwd) {
        std::cout << "password: ";
        std::getline(std::cin, new_pwd);
    }

    std::cout << "ok!";

    return 0;
}
