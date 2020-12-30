
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


auto print_number_from_queue(std::queue<int>& queue,
                             std::mutex& mtx,
                             int const id) -> void
{
    while (true) {
        if (queue.empty()) {
            std::cout << ("thread " + std::to_string(id) + " exiting\n");
            break;
        }

        auto number = int{};

        {
            std::unique_lock<std::mutex> lck{mtx};
            number = queue.front();
            queue.pop();
        }

        std::cout << ("from thread " + std::to_string(id) + ": "
                      + std::to_string(number) + "\n");
    }
}


auto main() -> int
{
    auto queue = std::queue<int>{};
    std::mutex mtx;

    for (auto i = 0; i < 100; i++) {
        queue.push(i);
    }

    auto t0 =
        std::thread{print_number_from_queue, std::ref(queue), std::ref(mtx), 0};
    auto t1 =
        std::thread{print_number_from_queue, std::ref(queue), std::ref(mtx), 1};
    auto t2 =
        std::thread{print_number_from_queue, std::ref(queue), std::ref(mtx), 2};
    auto t3 =
        std::thread{print_number_from_queue, std::ref(queue), std::ref(mtx), 3};


    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}