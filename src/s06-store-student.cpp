#include <fcntl.h>
#include <s22442/Student.h>
#include <sys/stat.h>
#include <unistd.h>

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

auto main() -> int
{
    auto const FILE_NAME = std::string{"./student.txt"};

    auto const FIRST_NAME    = std::string{"Kajetan"};
    auto const LAST_NAME     = std::string{"Welc"};
    auto const INDEX         = int{22442};
    auto const SEMESTER      = int{1};
    auto const AVERAGE_GRADE = double{4.5};

    auto student =
        s22442::Student{FIRST_NAME, LAST_NAME, INDEX, SEMESTER, AVERAGE_GRADE};


    auto student_file =
        open(FILE_NAME.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    auto file_content = std::ostringstream{};

    file_content << student.first_name << "\n"
                 << student.last_name << "\n"
                 << student.index << "\n"
                 << student.semester << "\n"
                 << student.average_grade << "\n";

    auto buf = file_content.str();
    auto n   = write(student_file, buf.data(), buf.size());
    if (n == -1) {
        perror("Something went wrong");
    }

    close(student_file);

    return 0;
}