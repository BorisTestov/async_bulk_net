#include "server.h"

Server::Server(boost::asio::io_service& io_service,
               const boost::asio::ip::tcp::endpoint& endpoint,
               std::shared_ptr<Stream> stream) :
    _acceptor(io_service, endpoint),
    _socket(io_service),
    _clients(),
    _stream(stream)
{
    accept();
}

void Server::accept()
{
    _acceptor.async_accept(
        _socket, [this](boost::system::error_code errorCode) {
            if (not errorCode)
            {
                auto session_new = std::make_shared<Session>(std::move(_socket), _clients, _stream);
                _clients.insert(session_new);
                session_new->start();
            }
            accept();
        });
}
