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
#include <sstream>
#include <string>
#include <thread>


auto cat_file(std::string const& file_path) -> std::string
{
    auto fd = open(file_path.c_str(), O_RDONLY, S_IRUSR);

    if (fd == -1) {
        return ":-(";
    }

    std::array<char, 4096> buf{0};
    auto const n = read(fd, buf.data(), buf.size());
    close(fd);

    if (n == -1) {
        return std::string{"File " + file_path
                           + " exists, but something went wrong"};
    }

    auto const cat_result = std::string{
        file_path + "\n" + std::string{buf.data(), static_cast<size_t>(n)}};

    return cat_result;
}


auto read_from_client(int client, std::string const client_addr) -> void
{
    std::array<char, 512> buffer{};
    while (auto const n = read(client, buffer.data(), buffer.size())) {
        auto const file_path = std::string{buffer.data(), buffer.data() + n};

        std::cout << client_addr << " >> " << file_path << "\n";

        auto const data = cat_file(file_path);

        write(client, data.data(), data.size());
    }
}


auto accept_clients(int const& sock) -> void
{
    sockaddr_in addr_of_a_client;
    memset(&addr_of_a_client, 0, sizeof(addr_of_a_client));
    auto addr_len = socklen_t{sizeof(addr_of_a_client)};

    while (auto client = accept(sock,
                                reinterpret_cast<sockaddr*>(&addr_of_a_client),
                                &addr_len)) {
        if (client != -1) {
            std::array<char, INET_ADDRSTRLEN + 1> buffer{};
            inet_ntop(AF_INET,
                      &addr_of_a_client.sin_addr,
                      buffer.data(),
                      buffer.size());

            auto tmp = std::ostringstream{};
            tmp << buffer.data() << ":" << be16toh(addr_of_a_client.sin_port);
            auto const client_addr = tmp.str();

            std::cout << "Connection received from " << client_addr << "\n";

            auto client_reader = std::thread{
                read_from_client, std::move(client), std::move(client_addr)};
            client_reader.detach();
        }
    }
}


auto await_exit_by_user() -> void
{
    auto input = std::string{};

    while (true) {
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
    }
}


auto main() -> int
{
    auto const IP   = std::string{"127.0.0.1"};
    auto const PORT = uint16_t{42420};

    std::cout << "Type \"exit\" to terminate the program\n";
    auto await_exit = std::thread{await_exit_by_user};

    auto sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htobe16(PORT);
    inet_pton(addr.sin_family, IP.c_str(), &addr.sin_addr);

    bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

    listen(sock, 0);
    std::cout << "Listening...\n";

    auto accept_connections = std::thread{accept_clients, std::ref(sock)};

    accept_connections.detach();

    await_exit.join();

    shutdown(sock, SHUT_RDWR);
    close(sock);

    return 0;
}