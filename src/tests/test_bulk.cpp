#include "server.h"
#include "session.h"
#include "stream.h"

#include <gtest/gtest.h>

TEST(network_bulk, ok)
{
    testing::internal::CaptureStdout();
    int port = 9000;
    int bulk_size = 3;
    std::cout << "Listening on port " << port << ", bulk size " << bulk_size << std::endl;

    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
    boost::asio::io_service service;

    Server host(service, ep, std::make_shared<Stream>(bulk_size));

    std::thread run_service([&service]() { service.run(); });
    run_service.detach();

    boost::asio::io_service testService;
    boost::asio::ip::tcp::socket socket(testService);
    socket.open(boost::asio::ip::tcp::v4());
    socket.connect(ep);
    socket.write_some(boost::asio::buffer("0\n1\n2\n3\n4\n5\n6\n7\n8\n"));
    boost::asio::deadline_timer timer(testService, boost::posix_time::seconds(5));
    timer.wait();
    socket.close();
    std::thread stop_service([&service]() { service.stop(); });
    stop_service.join();
    std::string output = testing::internal::GetCapturedStdout();
    std::string expectedOutput = "Listening on port 9000, bulk size 3\nbulk:0,1,2\nbulk:3,4,5\nbulk:6,7,8\n";
    ASSERT_EQ(output, expectedOutput);
}