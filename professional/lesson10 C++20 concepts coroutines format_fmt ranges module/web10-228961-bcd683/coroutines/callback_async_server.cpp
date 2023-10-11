#include <boost/asio.hpp>
#include <iostream>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket &&socket) : socket{std::move(socket)} {}

    void run()
    {
        socket.async_send(boost::asio::buffer("Ping\n"), [self = shared_from_this()](auto errc, size_t bytes_num)
                          {
            if (errc) {
                std::cerr << "Send error: " << errc.message() << "\n";
                return;
            }
            self->receive(); 
        });
    }

private:
    void receive()
    {
        std::vector<char> data(256);
        socket.async_receive(boost::asio::buffer(data), [self=shared_from_this(), data = std::move(data)](auto errc, size_t bytes_num)
                                   {
                if (errc) {
                    std::cerr << "Receive error: " << errc.message() << "\n";
                    return;
                }
                if (bytes_num == 0) {
                    std::cout << "zero";
                    self->receive();
                    return;
                }
                std::cout << "Received " << std::string_view{data.data(), data.size()} << "\n";
                self->socket.async_send(boost::asio::buffer(data), [self, data=std::move(data)](auto errc, size_t bytes_num) {
                    if (errc) {
                        std::cerr << "Final send error: " << errc.message() << "\n";
                        return;
                    }
                    std::cout << "Pong\n";
                    self->run();
                });
            });
    }

    boost::asio::ip::tcp::socket socket;
};

class Server
{
public:
    Server(boost::asio::io_context &context) : context{context}, acceptor{context}
    {
        boost::asio::ip::tcp::endpoint ep{boost::asio::ip::make_address_v4("127.0.0.1"), 4242};
        acceptor.open(ep.protocol());
        acceptor.bind(ep);
    }

    void run(std::function<void(std::shared_ptr<Session>)> on_accept)
    {
        acceptor.listen();
        auto client_socket = std::make_unique<boost::asio::ip::tcp::socket>(context);
        acceptor.async_accept(*client_socket, [this, client_socket = std::move(client_socket), on_accept](boost::system::error_code errc) mutable
                              {
            if (errc) {
                std::cerr << "Accept error: [" << errc.category().name() << "] " << errc.message() << "\n";
            } else {
                auto session = std::make_shared<Session>(std::move(*client_socket));
                client_socket.release();
                on_accept(session);
            }
            run(on_accept); });
    }

private:
    boost::asio::io_context &context;
    boost::asio::ip::tcp::acceptor acceptor;
};

int main()
{
    boost::asio::io_context context;
    Server server{context};
    server.run([](auto session)
               { session->run(); });
    context.run();
}