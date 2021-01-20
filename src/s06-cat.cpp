
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>


auto main(int argc, char* argv[]) -> int
{
    if (argc == 1) {
        return 1;
    }

    auto const file_name = std::string{argv[1]};

    auto fd = open(file_name.c_str(), O_RDONLY, S_IRUSR);

    if (fd == -1) {
        perror(std::string{"Cannot find " + file_name}.c_str());
        return 0;
    }

    struct stat info;
    memset(&info, 0, sizeof(info));
    auto const r = fstat(fd, &info);

    if (r == -1) {
        perror("Cannot read the file size");
        return 1;
    }

    std::array<char, info.st_size> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    close(fd);

    if (n == -1) {
        perror("Something went wrong");
        return 1;
    }

    std::cout << std::string{buf.data(), static_cast<size_t>(n)};

    return 0;
}