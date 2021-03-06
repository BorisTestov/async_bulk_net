#include "session.h"

Session::Session(boost::asio::ip::tcp::socket socket,
                 std::set<std::shared_ptr<Session>>& container,
                 std::shared_ptr<Stream> stream) :
    _socket(std::move(socket)),
    _read_line(""),
    _container(container),
    _stream(stream)
{}

void Session::start()
{
    read();
}

void Session::read()
{
    auto self(shared_from_this());
    boost::asio::async_read(_socket,
                            boost::asio::buffer(&_symbol, 1),
                            [this, self](boost::system::error_code errorCode, std::size_t length) {
                                (void) length;
                                if (not errorCode)
                                {
                                    if ('\n' != _symbol)
                                    {
                                        _read_line += _symbol;
                                    }
                                    else
                                    {
                                        if ('\r' == _read_line.back())
                                        {
                                            _read_line.pop_back();
                                        }
                                        _stream->commonInput(_read_line);
                                        _read_line.clear();
                                    }
                                    read();
                                }
                                else
                                {
                                    _container.erase(self);
                                    _socket.close();
                                    if (_container.empty())
                                        _stream->flush();
                                }
                            });
}
