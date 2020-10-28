#pragma once

#include "block_processor.h"
#include "stream.h"

#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket socket,
            std::set<std::shared_ptr<Session>>& container,
            std::shared_ptr<Stream> stream);
    virtual ~Session() = default;
    void start();

private:
    void read();
    boost::asio::ip::tcp::socket _socket;
    char _symbol;
    std::string _read_line;
    std::set<std::shared_ptr<Session>>& _container;
    std::shared_ptr<Stream> _stream;
    size_t _blockCounter;
    BlockProcessor _processor;
};