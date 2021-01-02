
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <string>
#include <thread>


auto bounce(int& number,
            std::string& turn,
            std::mutex& mtx,
            std::condition_variable& cv,
            std::random_device& rd,
            std::uniform_int_distribution<int>& d,
            std::string const id,
            std::string const bounce_to) -> void
{
    while (true) {
        std::unique_lock<std::mutex> lck{mtx};

        while (turn != id) {
            cv.wait(lck);
        }

        std::cout << (id + " " + std::to_string(number) + "\n");

        number += d(rd);

        turn = bounce_to;

        cv.notify_all();

        if (number > 1024) {
            break;
        }
    }
}


auto main() -> int
{
    std::mutex mtx;
    std::condition_variable cv;

    std::random_device rd;
    std::uniform_int_distribution<int> d1_42(1, 42);

    auto turn   = std::string{"ping"};
    auto number = int{d1_42(rd)};

    auto ping = std::thread(bounce,
                            std::ref(number),
                            std::ref(turn),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(d1_42),
                            "ping",
                            "pong");

    auto pong = std::thread(bounce,
                            std::ref(number),
                            std::ref(turn),
                            std::ref(mtx),
                            std::ref(cv),
                            std::ref(rd),
                            std::ref(d1_42),
                            "pong",
                            "ping");


    ping.join();
    pong.join();

    return 0;
}