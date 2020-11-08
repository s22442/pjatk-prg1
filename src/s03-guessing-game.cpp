
#include <iostream>
#include <random>
#include <string>

auto main() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> d100(1, 100);

    auto const guess_me = d100(rd);

    auto raw_input = std::string{};
    auto int_input = int{};

    while (true) {
        std::cout << "guess: ";
        std::getline(std::cin, raw_input);

        int_input = std::stoi(raw_input);

        if (int_input == guess_me)
            break;

        if (int_input < guess_me) {
            std::cout << "number too small!";
        } else {
            std::cout << "number too big!";
        }

        std::cout << "\n";
    }

    std::cout << "just right!";

    return 0;
}
