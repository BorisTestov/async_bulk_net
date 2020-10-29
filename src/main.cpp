#include "server.h"
#include "session.h"
#include "stream.h"
#include "version.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Current version: " << version() << std::endl;
    if (argc != 3)
    {
        std::cout << "Usage: bulk_server <port> <bulk_size>" << std::endl;
        return -1;
    };

    int port = std::stoi(argv[1]);
    int bulk_size = std::stoi(argv[2]);
    std::cout << "Listening on port " << port << ", bulk size " << bulk_size << std::endl;

    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
    boost::asio::io_service service;

    Server host(service, ep, std::make_shared<Stream>(bulk_size));

    service.run();
    return 0;
}
