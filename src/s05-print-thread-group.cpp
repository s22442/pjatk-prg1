
#include <iostream>
#include <string>
#include <thread>
#include <vector>

auto print_string(std::string text) -> void
{
    std::cout << text << "\n";
}

auto main() -> int
{
    auto const GROUP_SIZE  = int{6};
    auto const GROUP_COUNT = int{7};

    for (auto i = 0; i < GROUP_COUNT; i++) {
        std::cout << "Group " << i << ":\n";

        std::vector<std::thread> hello_threads;

        for (auto j = 0; j < GROUP_SIZE; j++) {
            auto text = std::string{"Hello, "
                                    + std::to_string(j + i * GROUP_SIZE) + "!"};

            hello_threads.push_back(std::thread{print_string, std::move(text)});
        }

        for (auto& each : hello_threads) {
            each.join();
        }
    }

    return 0;
}
