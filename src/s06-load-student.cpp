#include <fcntl.h>
#include <s22442/Student.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <vector>

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
    auto const FILE_NAME = std::string{"./student.txt"};

    auto student_file = open(FILE_NAME.c_str(), O_RDONLY, S_IRUSR);

    std::array<char, 4096> buf{0};
    auto const n = read(student_file, buf.data(), buf.size());
    close(student_file);

    if (n == -1) {
        perror("Something went wrong");
        return 1;
    }

    std::vector<std::string> file_lines;

    auto file_content = std::stringstream{};
    file_content << std::string{buf.data(), static_cast<size_t>(n)};
    auto line = std::string{};

    while (std::getline(file_content, line)) {
        file_lines.push_back(line);
    }

    auto student = s22442::Student{file_lines[0],
                                   file_lines[1],
                                   std::stoi(file_lines[2]),
                                   std::stoi(file_lines[3]),
                                   std::stod(file_lines[4])};

    std::cout << student.to_string();

    return 0;
}