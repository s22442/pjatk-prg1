
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


auto print_string_from_queue(std::queue<std::string>& queue,
                             std::mutex& mtx,
                             std::condition_variable& cv,
                             int const id) -> void
{
    while (true) {
        std::unique_lock<std::mutex> lck{mtx};
        cv.wait(lck);

        auto line = queue.front();
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
    std::condition_variable cv;

    auto t0 = std::thread{print_string_from_queue,
                          std::ref(queue),
                          std::ref(mtx),
                          std::ref(cv),
                          0};
    auto t1 = std::thread{print_string_from_queue,
                          std::ref(queue),
                          std::ref(mtx),
                          std::ref(cv),
                          1};
    auto t2 = std::thread{print_string_from_queue,
                          std::ref(queue),
                          std::ref(mtx),
                          std::ref(cv),
                          2};
    auto t3 = std::thread{print_string_from_queue,
                          std::ref(queue),
                          std::ref(mtx),
                          std::ref(cv),
                          3};

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
        cv.notify_one();

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