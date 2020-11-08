
#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    int beer = argv[1] ? std::stoi(argv[1]) : 99;

    for (auto i = beer; i > 0; i--) {
        std::cout << i << " bottles of beer on the wall, " << i
                  << " bottles of beer.\n";
        std::cout << "Take one down, pass it around, " << i - 1
                  << " bottles of beer on the wall...\n\n";
    }

    std::cout
        << "No more bottles of beer on the wall, no more bottles of beer.\n";
    std::cout << "Go to the store and buy some more, " << beer
              << " bottles of beer on the wall...";

    return 0;
}
