
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    if (argc == 0) {
        return 1;
    }

    for (auto i = 1; i < argc; i++) {
        std::cout << " " << argv[i];
    }

    return 0;
}
