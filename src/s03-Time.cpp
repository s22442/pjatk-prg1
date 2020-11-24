#include <s22442/Time.h>

#include <iostream>

s22442::Time::Time(int h, int m, int s) : hours{h}, minutes{m}, seconds{s}
{}

auto s22442::Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};

    out << (hours < 10 ? "0" : "") << hours << ":";
    out << (minutes < 10 ? "0" : "") << minutes << ":";
    out << (seconds < 10 ? "0" : "") << seconds << "\n";

    return out.str();
}

auto s22442::Time::next_hour() -> void
{
    hours = hours == 23 ? 0 : ++hours;
}

auto s22442::Time::next_minute() -> void
{
    minutes = minutes == 59 ? 0 : ++minutes;

    if (!minutes) {
        next_hour();
    }
}

auto s22442::Time::next_second() -> void
{
    seconds = seconds == 59 ? 0 : ++seconds;

    if (!seconds) {
        next_minute();
    }
}

auto s22442::Time::time_of_day() const -> Time_of_day
{
    if (hours >= 6 && hours < 10) {
        return Time_of_day::Morning;
    }

    if (hours >= 10 && hours < 17) {
        return Time_of_day::Day;
    }

    if (hours >= 17 && hours < 21) {
        return Time_of_day::Evening;
    }

    return Time_of_day::Night;
}

auto s22442::Time::to_string(Time_of_day tod) const -> std::string
{
    switch (tod) {
    case Time_of_day::Morning:
        return "Morning\n";

    case Time_of_day::Day:
        return "Day\n";

    case Time_of_day::Evening:
        return "Evening\n";

    case Time_of_day::Night:
        return "Night\n";
    }
}

auto s22442::Time::previous_hour() -> void
{
    hours = hours ? --hours : 23;
}

auto s22442::Time::previous_minute() -> void
{
    minutes = minutes ? --minutes : 59;

    if (minutes == 59) {
        previous_hour();
    }
}

auto s22442::Time::previous_second() -> void
{
    seconds = seconds ? --seconds : 59;

    if (seconds == 59) {
        previous_minute();
    }
}

auto s22442::Time::add_hours(int h) -> void
{
    while (h > 0) {
        next_hour();
        h--;
    }

    while (h < 0) {
        previous_hour();
        h++;
    }
}

auto s22442::Time::add_minutes(int m) -> void
{
    while (m > 0) {
        next_minute();
        m--;
    }

    while (m < 0) {
        previous_minute();
        m++;
    }
}

auto s22442::Time::add_seconds(int s) -> void
{
    while (s > 0) {
        next_second();
        s--;
    }

    while (s < 0) {
        previous_second();
        s++;
    }
}

auto s22442::Time::operator+(Time const& time) const -> Time
{
    auto new_time = Time{hours, minutes, seconds};

    new_time.add_seconds(time.seconds);
    new_time.add_minutes(time.minutes);
    new_time.add_hours(time.hours);

    return new_time;
}

auto s22442::Time::operator-(Time const& time) const -> Time
{
    auto new_time = Time{hours, minutes, seconds};

    new_time.add_seconds(-time.seconds);
    new_time.add_minutes(-time.minutes);
    new_time.add_hours(-time.hours);

    return new_time;
}

auto s22442::Time::operator<(Time const& time) const -> bool
{
    if (hours != time.hours) {
        return hours < time.hours;
    }

    if (minutes != time.minutes) {
        return minutes < time.minutes;
    }

    return seconds < time.seconds;
}

auto s22442::Time::operator>(Time const& time) const -> bool
{
    if (hours != time.hours) {
        return hours > time.hours;
    }

    if (minutes != time.minutes) {
        return minutes > time.minutes;
    }

    return seconds > time.seconds;
}

auto s22442::Time::operator==(Time const& time) const -> bool
{
    return hours == time.hours && minutes == time.minutes
           && seconds == time.seconds;
}

auto s22442::Time::operator!=(Time const& time) const -> bool
{
    return !operator==(time);
}

auto s22442::Time::count_minutes() const -> uint64_t
{
    return minutes + hours * 60;
}

auto s22442::Time::count_seconds() const -> uint64_t
{
    return seconds + count_minutes() * 60;
}

auto s22442::Time::time_to_midnight() const -> Time
{
    return Time{0, 0, 0}.operator-(Time{hours, minutes, seconds});
}

auto main() -> int
{
    auto const SLIDE_25_HOUR   = int{23};
    auto const SLIDE_25_MINUTE = int{59};
    auto const SLIDE_25_SECOND = int{59};

    auto const SLIDE_27_HOUR_A   = int{12};
    auto const SLIDE_27_MINUTE_A = int{34};
    auto const SLIDE_27_SECOND_A = int{56};
    auto const SLIDE_27_HOUR_B   = int{5};
    auto const SLIDE_27_MINUTE_B = int{15};
    auto const SLIDE_27_SECOND_B = int{45};

    auto slide_25_time =
        s22442::Time{SLIDE_25_HOUR, SLIDE_25_MINUTE, SLIDE_25_SECOND};

    auto slide_27_time_a =
        s22442::Time{SLIDE_27_HOUR_A, SLIDE_27_MINUTE_A, SLIDE_27_SECOND_A};
    auto slide_27_time_b =
        s22442::Time{SLIDE_27_HOUR_B, SLIDE_27_MINUTE_B, SLIDE_27_SECOND_B};


    // Slide 25
    std::cout << "** SLIDE 25 **\n";

    std::cout << "Initial time:\n";
    std::cout << slide_25_time.to_string();

    std::cout << "+1 second:\n";
    slide_25_time.next_second();
    std::cout << slide_25_time.to_string();

    std::cout << "+1 minute:\n";
    slide_25_time.next_minute();
    std::cout << slide_25_time.to_string();

    std::cout << "+1 hour:\n";
    slide_25_time.next_hour();
    std::cout << slide_25_time.to_string();

    // Slide 26
    std::cout << "** SLIDE 26 **\n";

    std::cout << "Time of day:\n";
    std::cout << slide_25_time.to_string(slide_25_time.time_of_day());

    // Slide 27
    std::cout << "** SLIDE 27 **\n";

    std::cout << "Time A:\n";
    std::cout << slide_27_time_a.to_string();
    std::cout << slide_27_time_a.to_string(slide_27_time_a.time_of_day());
    std::cout << "Time B:\n";
    std::cout << slide_27_time_b.to_string();
    std::cout << slide_27_time_b.to_string(slide_27_time_b.time_of_day());

    auto slide_27_ab_addition_time = slide_27_time_a.operator+(slide_27_time_b);
    auto slide_27_ab_subtraction_time =
        slide_27_time_a.operator-(slide_27_time_b);

    std::cout << "Time A + Time B:\n";
    std::cout << slide_27_ab_addition_time.to_string();
    std::cout << slide_27_ab_addition_time.to_string(
        slide_27_ab_addition_time.time_of_day());

    std::cout << "Time A - Time B:\n";
    std::cout << slide_27_ab_subtraction_time.to_string();
    std::cout << slide_27_ab_subtraction_time.to_string(
        slide_27_ab_subtraction_time.time_of_day());

    std::cout << "Time A < Time B:\n";
    std::cout << slide_27_time_a.operator<(slide_27_time_b) << "\n";

    std::cout << "Time A > Time B:\n";
    std::cout << slide_27_time_a.operator>(slide_27_time_b) << "\n";

    std::cout << "Time A == Time B:\n";
    std::cout << slide_27_time_a.operator==(slide_27_time_b) << "\n";

    std::cout << "Time A != Time B:\n";
    std::cout << slide_27_time_a.operator!=(slide_27_time_b) << "\n";

    // Slide 28
    std::cout << "** SLIDE 28 **\n";

    std::cout << "Seconds of time A:\n";
    std::cout << slide_27_time_a.count_seconds() << "\n";

    std::cout << "Minutes of time A:\n";
    std::cout << slide_27_time_a.count_minutes() << "\n";

    std::cout << "Time until midnight for time A:\n";
    std::cout << slide_27_time_a.time_to_midnight().to_string();

    return 0;
}