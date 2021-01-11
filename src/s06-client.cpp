#include <arpa/inet.h>
#include <endian.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>

auto main() -> int
{
    auto sock       = socket(AF_INET, SOCK_STREAM, 0);
    auto const ip   = std::string{"127.0.0.1"};
    auto const port = uint16_t{42420};

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(port);
    inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);

    connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    {
        auto data = std::string{};

        std::cout << "Send something to server: ";
        std::getline(std::cin, data);

        write(sock, data.data(), data.size());
    }
    {
        std::array<char, 512> buffer{};
        auto const n    = read(sock, buffer.data(), buffer.size());
        auto const data = std::string{buffer.data(), buffer.data() + n};

        std::cout << "DATA FROM SERVER:\n";
        std::cout << data << "\n";
    }

    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}