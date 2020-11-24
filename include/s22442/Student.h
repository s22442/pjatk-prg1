#ifndef S22442_STUDENT_H
#define S22442_STUDENT_H

#include <sstream>
#include <string>


namespace s22442 {

struct Student {
    std::string const first_name;
    std::string const last_name;
    int const index;
    int semester;
    double average_grade;

    Student(std::string, std::string, int, int, double);

    auto to_string() const -> std::string;
};

}  // namespace s22442

#endif