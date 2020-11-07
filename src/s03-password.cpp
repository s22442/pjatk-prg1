
#include <iostream>
#include <string>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    auto const pwd = std::string{argv[1]};

    std::string newPwd;

    while (pwd != newPwd)
    {
        std::cout << "\nPassword: ";
        std::cin >> newPwd;
    }

    std::cout << "\nOk!";

    return 0;
}
