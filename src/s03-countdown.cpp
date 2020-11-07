
#include <iostream>
#include <cstdlib>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    auto const count = atoi(argv[1]);

    for (auto i = count; i >= 0; i--)
    {
        std::cout << i << "...\n";
    }

    return 0;
}
