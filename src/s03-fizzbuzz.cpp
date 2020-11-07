
#include <iostream>
#include <cstdlib>

auto main(int argc, char *argv[]) -> int
{
    if (argc == 0)
    {
        return 1;
    }

    auto const number = atoi(argv[1]);

    for (auto n = 1; n <= number; n++)
    {
        std::cout << "n: " << n << "\n";

        if (!(n % 3))
            std::cout << "Fizz";

        if (!(n % 5))
            std::cout << "Buzz";

        std::cout << "\n\n";
    }

    return 0;
}
