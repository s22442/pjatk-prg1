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
    auto const IP   = std::string{"127.0.0.1"};
    auto const PORT = uint16_t{42420};

    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(PORT);
    inet_pton(addr.sin_family, IP.c_str(), &addr.sin_addr);

    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    listen(sock, 0);

    auto client = accept(sock, nullptr, nullptr);

    {
        std::array<char, 512> buffer{};
        while (auto const n = read(client, buffer.data(), buffer.size())) {
            auto const data = std::string{buffer.data(), buffer.data() + n};

            std::cout << "DATA FROM A CLIENT:\n";
            std::cout << data << "\n";

            write(client, data.data(), data.size());
        }
    }

    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}