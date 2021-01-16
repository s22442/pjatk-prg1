
#include <s22442/s06-server.h>

#include <random>
#include <vector>

std::random_device rd;
std::vector<std::string> random_notes;


auto s22442::server::do_something_with_client_data(int const& client,
                                                   std::string const data) const
    -> void
{
    random_notes.push_back(std::move(data));

    std::uniform_int_distribution<int> d(0, random_notes.size() - 1);
    auto const random_note = random_notes[d(rd)];

    write(client, random_note.data(), random_note.size());
}


auto main() -> int
{
    auto const IP   = std::string{"127.0.0.1"};
    auto const PORT = uint16_t{42420};

    auto server = s22442::server{IP, PORT};
    server.start();

    return 0;
}