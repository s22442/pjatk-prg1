
#include <iostream>
#include <string>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    auto const pwd = std::string{argv[1]};

    auto new_pwd = std::string{};

    while (pwd != new_pwd)
    {
        std::cout << "\nPassword: ";
        std::cin >> new_pwd;
    }

    std::cout << "\nOk!";

    return 0;
}
