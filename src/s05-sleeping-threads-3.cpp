#include <itp/channel.h>

#include <iostream>
#include <string>
#include <thread>


auto print_string_from_queue(itp::channel<std::string>& ch, int const id)
    -> void
{
    while (true) {
        auto line = ch.wait();

        if (line.empty()) {
            std::cout << ("thread " + std::to_string(id) + " exiting\n");
            break;
        }

        std::cout << ("from thread " + std::to_string(id) + ": " + line + "\n");
    }
}


auto main() -> int
{
    auto ch = itp::channel<std::string>{};

    auto t0 = std::thread{print_string_from_queue, std::ref(ch), 0};
    auto t1 = std::thread{print_string_from_queue, std::ref(ch), 1};
    auto t2 = std::thread{print_string_from_queue, std::ref(ch), 2};
    auto t3 = std::thread{print_string_from_queue, std::ref(ch), 3};

    auto empty_line_count = int{0};

    while (true) {
        auto line = std::string{};
        std::getline(std::cin, line);

        if (line.empty()) {
            empty_line_count++;
        }

        ch.push(line);

        if (empty_line_count >= 4) {
            break;
        }
    }

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}