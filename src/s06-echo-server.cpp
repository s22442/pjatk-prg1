
#include <s22442/s06-server.h>


auto s22442::server::do_something_with_client_data(int const& client,
                                                   std::string const data) const
    -> void
{
    write(client, data.data(), data.size());
}


auto main() -> int
{
    auto const IP   = std::string{"127.0.0.1"};
    auto const PORT = uint16_t{42420};

    auto server = s22442::server{IP, PORT};
    server.start();

    return 0;
}