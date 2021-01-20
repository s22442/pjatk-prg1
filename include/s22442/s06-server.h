#ifndef S22442_STUDENT_H
#define S22442_STUDENT_H

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


namespace s22442 {

struct server {
  private:
    sockaddr_in addr;
    int sock;

    auto do_something_with_client_data(int const&, std::string const) const
        -> void;


    auto read_from_client(int client, std::string const client_addr) const
        -> void
    {
        std::array<char, 512> buffer{};
        while (auto const n = read(client, buffer.data(), buffer.size())) {
            if (n == -1) {
                break;
            }

            auto const data = std::string{buffer.data(), buffer.data() + n};

            std::cout << client_addr << " >> " << data << "\n";

            do_something_with_client_data(std::ref(client), std::move(data));
        }

        std::cout << "Connection to " << client_addr << " has been closed\n";
    }

    auto accept_clients() -> void
    {
        sockaddr_in addr_of_a_client;
        memset(&addr_of_a_client, 0, sizeof(addr_of_a_client));
        auto addr_len = socklen_t{sizeof(addr_of_a_client)};

        while (auto client =
                   accept(sock,
                          reinterpret_cast<sockaddr*>(&addr_of_a_client),
                          &addr_len)) {
            if (client == -1) {
                continue;
            }

            std::array<char, INET_ADDRSTRLEN + 1> buffer{};
            inet_ntop(AF_INET,
                      &addr_of_a_client.sin_addr,
                      buffer.data(),
                      buffer.size());

            auto tmp_client_addr = std::ostringstream{};
            tmp_client_addr << buffer.data() << ":"
                            << be16toh(addr_of_a_client.sin_port);
            auto const client_addr = tmp_client_addr.str();

            std::cout << "Connection received from " << client_addr << "\n";

            auto client_reader = std::thread{[&] {
                read_from_client(std::move(client), std::move(client_addr));
            }};
            client_reader.detach();
        }
    }

    auto await_exit_by_user() const -> void
    {
        auto input = std::string{};

        while (true) {
            std::getline(std::cin, input);

            if (input == "exit") {
                break;
            }
        }
    }


  public:
    server(std::string const ip, uint16_t const port)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port   = htobe16(port);
        inet_pton(addr.sin_family, ip.c_str(), &addr.sin_addr);
    }

    auto start() -> void
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));

        std::cout << "Type \"exit\" to terminate the program\n";

        listen(sock, 0);
        std::cout << "Listening...\n";

        auto connection_accepter = std::thread{[this] { accept_clients(); }};
        connection_accepter.detach();

        auto exit_awaitor = std::thread{[this] { await_exit_by_user(); }};
        exit_awaitor.join();

        shutdown(sock, SHUT_RDWR);
        close(sock);
    }
};

}  // namespace s22442

#endif