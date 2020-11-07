
#include <iostream>
#include <string>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    auto const pwd = std::string{argv[1]};

    std::string new_pwd;

    while (pwd != new_pwd)
    {
        std::cout << "\nPassword: ";
        std::cin >> new_pwd;
    }

    std::cout << "\nOk!";

    return 0;
}
