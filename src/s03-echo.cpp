
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));

    args.erase(args.begin());

    auto print_newline = true;
    auto reverse_args  = false;
    auto separator     = " ";

    if (args.at(0) == "-r") {
        args.erase(args.begin());
        reverse_args = true;
    }

    if (args.at(0) == "-l") {
        args.erase(args.begin());
        separator = "\n";
    } else if (args.at(0) == "-n") {
        args.erase(args.begin());
        print_newline = false;
    }

    if (reverse_args) {
        std::reverse(args.begin(), args.end());
    }

    for (auto const& each : args) {
        std::cout << each << separator;
    }

    if (print_newline) {
        std::cout << "\n";
    }

    return 0;
}
