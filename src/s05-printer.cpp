// Source:
// https://git.sr.ht/~maelkum/education-introduction-to-programming-cxx/tree/master/item/src/concurrency-channel.cpp

#include <itp/channel.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>


auto printer(itp::channel<std::string>& ch) -> void
{
    std::cout << "printer is running!\n";

    std::string message = ch.wait();
    while (!message.empty()) {
        std::cout << message << "\n";
        try {
            message = ch.wait_for(std::chrono::milliseconds{334});
        } catch (itp::timeout_expired_error const&) {
            // timeout expired, ignore
        }
    }

    std::cout << "printer is shutting down!\n";
}

auto main() -> int
{
    auto ch = itp::channel<std::string>{};
    auto th = std::thread{printer, std::ref(ch)};

    {
        auto message = std::string{};
        do {
            std::getline(std::cin, message);
            ch.push(message);
        } while (!message.empty());
    }

    th.join();

    return 0;
}