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
#include <thread>


auto send_to_server(int const& sock) -> void
{
    std::cout << "Send an empty line to terminate the connection and exit the "
                 "program\n"
              << "Go ahead, type something:\n";

    auto data = std::string{};
    while (true) {
        std::getline(std::cin, data);

        if (data.empty()) {
            break;
        }

        write(sock, data.data(), data.size());
    }
}


auto read_from_server(int const& sock) -> void
{
    std::array<char, 512> buffer{};
    while (auto const n = read(sock, buffer.data(), buffer.size())) {
        if (n == -1) {
            break;
        }

        auto const data = std::string{buffer.data(), buffer.data() + n};

        std::cout << "SERVER >> " << data << "\n";
    }

    std::cout << "Connection to the server has been lost\n";
}


auto main() -> int
{
    auto const SERVER_IP   = std::string{"127.0.0.1"};
    auto const SERVER_PORT = uint16_t{42420};

    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(SERVER_PORT);
    inet_pton(addr.sin_family, SERVER_IP.c_str(), &addr.sin_addr);

    std::cout << "Connecting to " << SERVER_IP << ":"
              << std::to_string(SERVER_PORT) << " ...\n";

    auto server_sock =
        connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    if (server_sock == -1) {
        perror("Unable to connect to the server");
    } else {
        std::cout << "Connected successfully\n";

        auto to_server   = std::thread{send_to_server, std::ref(sock)};
        auto from_server = std::thread{read_from_server, std::ref(sock)};

        to_server.join();
        from_server.detach();
    }

    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}