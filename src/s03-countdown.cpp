
#include <iostream>
#include <string>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    for (auto i = std::stoi(argv[1]); i >= 0; i--)
    {
        std::cout << i << "...\n";
    }

    return 0;
}
