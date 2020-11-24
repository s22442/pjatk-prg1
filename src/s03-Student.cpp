#include <s22442/Student.h>

#include <iostream>

s22442::Student::Student(std::string fn,
                         std::string ln,
                         int i,
                         int s,
                         double ag)
        : first_name{fn}
        , last_name{ln}
        , index{i}
        , semester{s}
        , average_grade{ag}
{}

auto s22442::Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};

    out << "First name: " << first_name << "\n"
        << "Last name: " << last_name << "\n"
        << "Index number: " << index << "\n"
        << "Semester: " << semester << "\n"
        << "Average grade: " << average_grade << "\n";

    return out.str();
}

auto main() -> int
{
    auto const FIRST_NAME    = std::string{"Kajetan"};
    auto const LAST_NAME     = std::string{"Welc"};
    auto const INDEX         = int{22442};
    auto const SEMESTER      = int{1};
    auto const AVERAGE_GRADE = double{4.5};

    auto student =
        s22442::Student{FIRST_NAME, LAST_NAME, INDEX, SEMESTER, AVERAGE_GRADE};

    std::cout << student.to_string();

    return 0;
}