
#include <s22442/s06-server.h>


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


auto s22442::server::do_something_with_client_data(int const& client,
                                                   std::string const data) const
    -> void
{
    auto const data_from_cat = cat_file(data);

    write(client, data_from_cat.data(), data_from_cat.size());
}


auto main() -> int
{
    auto const IP   = std::string{"127.0.0.1"};
    auto const PORT = uint16_t{42420};

    auto server = s22442::server{IP, PORT};
    server.start();

    return 0;
}