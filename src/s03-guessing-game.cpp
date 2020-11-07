
#include <iostream>
#include <random>

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    auto const guess_me = d100(rd);

    int input;

    while (true)
    {
        std::cout << "\nguess: ";
        std::cin >> input;

        if (input == guess_me)
            break;

        if (input < guess_me)
            std::cout << "number too small!";
        else
            std::cout << "number too big!";
    }

    std::cout << "just right!";

    return 0;
}
