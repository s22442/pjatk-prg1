#ifndef S22442_TIME_H
#define S22442_TIME_H

#include <sstream>
#include <string>


namespace s22442 {

struct Time {
    int hours;
    int minutes;
    int seconds;

    enum class Time_of_day { Morning, Day, Evening, Night };

    Time(int, int, int);

    // Slide 25
    auto to_string() const -> std::string;
    auto next_hour() -> void;
    auto next_minute() -> void;
    auto next_second() -> void;

    // Slide 26
    auto time_of_day() const -> Time_of_day;
    auto to_string(Time_of_day const&) const -> std::string;

    // Slide 27
    auto operator+(Time const&) const -> Time;
    auto operator-(Time const&) const -> Time;
    auto operator<(Time const&) const -> bool;
    auto operator>(Time const&) const -> bool;
    auto operator==(Time const&) const -> bool;
    auto operator!=(Time const&) const -> bool;

    // Slide 27 helper functions
    auto previous_hour() -> void;
    auto previous_minute() -> void;
    auto previous_second() -> void;
    auto add_hours(int) -> void;
    auto add_minutes(int) -> void;
    auto add_seconds(int) -> void;

    // Slide 28
    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() const -> Time;
};

}  // namespace s22442

#endif