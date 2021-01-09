
#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto print_string_from_queue(std::queue<std::string>& queue,
                             std::mutex& mtx,
                             int const id) -> void
{
    std::random_device rd;
    std::uniform_int_distribution<int> d10_100(10, 100);

    while (true) {
        std::unique_lock<std::mutex> lck{mtx};

        if (queue.empty()) {
            lck.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(d10_100(rd)));
            continue;
        }

        auto line = std::string{};

        line = queue.front();
        queue.pop();

        if (line.empty()) {
            std::cout << ("thread " + std::to_string(id) + " exiting\n");
            break;
        }

        std::cout << ("from thread " + std::to_string(id) + ": " + line + "\n");
    }
}


auto main() -> int
{
    auto queue = std::queue<std::string>{};
    std::mutex mtx;

    auto t0 =
        std::thread{print_string_from_queue, std::ref(queue), std::ref(mtx), 0};
    auto t1 =
        std::thread{print_string_from_queue, std::ref(queue), std::ref(mtx), 1};
    auto t2 =
        std::thread{print_string_from_queue, std::ref(queue), std::ref(mtx), 2};
    auto t3 =
        std::thread{print_string_from_queue, std::ref(queue), std::ref(mtx), 3};

    auto empty_line_count = int{0};

    while (true) {
        auto line = std::string{};
        std::getline(std::cin, line);

        if (line.empty()) {
            empty_line_count++;
        }

        {
            std::unique_lock<std::mutex> lck{mtx};
            queue.push(std::move(line));
        }

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