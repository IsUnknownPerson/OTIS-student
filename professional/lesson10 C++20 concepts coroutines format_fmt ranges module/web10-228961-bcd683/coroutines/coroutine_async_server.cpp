#include <boost/asio.hpp>
#include <iostream>
#include <span>

#include "coroutine.hpp"

template <typename T>
class task
{
public:
    struct promise_type
    {
        coro::suspend_never initial_suspend()
        {
            return {};
        }
        coro::suspend_never final_suspend() noexcept
        {
            return {};
        }
        void unhandled_exception() { std::terminate(); }
        task get_return_object()
        {
            return {};
        }
        void return_void() {}
    };
};

using Socket = boost::asio::ip::tcp::socket;
using Acceptor = boost::asio::ip::tcp::acceptor;

auto async_send(Socket &socket, std::span<const char> data)
{
    struct Awaitable
    {
        bool await_ready() const { return false; }

        void await_suspend(coro::coroutine_handle<> coro)
        {
            socket.async_send(boost::asio::buffer(data), [this, coro](auto errc, size_t bytes_num) mutable
                              {
                ec = errc;
                coro.resume(); });
        }

        boost::system::error_code await_resume()
        {
            return ec;
        }
        Socket &socket;
        std::span<const char> data;
        boost::system::error_code ec;
    };
    return Awaitable{socket, data};
}

auto async_receive(Socket &socket)
{
    struct Awaitable
    {
        bool await_ready() const { return false; }

        void await_suspend(coro::coroutine_handle<> coro)
        {
            data.resize(256);
            socket.async_receive(boost::asio::buffer(data), [this, coro](auto errc, size_t bytes_num) mutable
                                 {
                ec = errc;
                coro.resume(); });
        }

        std::pair<boost::system::error_code, std::string> await_resume()
        {
            return {ec, std::move(data)};
        }
        Socket &socket;
        std::string data;
        boost::system::error_code ec;
    };
    return Awaitable{socket};
}


auto async_accept(boost::asio::io_context &context, Acceptor &acceptor)
{
    struct Awaitable
    {
        Awaitable(boost::asio::io_context &context, Acceptor &acceptor) : context{context}, acceptor{acceptor} {}

        bool await_ready() const { return false; }
        void await_suspend(coro::coroutine_handle<> coro)
        {
            client_socket = std::make_unique<boost::asio::ip::tcp::socket>(context);
            acceptor.async_accept(*client_socket, [this, coro](boost::system::error_code errc) mutable
                                  { ec = errc; coro.resume(); });
        }
        std::pair<boost::system::error_code, std::unique_ptr<Socket>> await_resume()
        {
            return {ec, std::move(client_socket)};
        }

        std::unique_ptr<Socket> client_socket;
        boost::asio::io_context &context;
        Acceptor &acceptor;
        boost::system::error_code ec;
    };
    return Awaitable{context, acceptor};
}


task<void> session(std::unique_ptr<Socket> socket)
{
    while (true)
    {
        auto send_ec = co_await async_send(*socket, "Ping");
        if (send_ec)
        {
            std::cerr << "Send error: " << send_ec.message() << "\n";
            co_return;
        }
        auto &&[recv_ec, data] = co_await async_receive(*socket);
        if (recv_ec)
        {
            std::cerr << "Receive error: " << recv_ec.message() << "\n";
            co_return;
        }
        send_ec = co_await async_send(*socket, data);
        if (send_ec)
        {
            std::cerr << "Send error: " << send_ec.message() << "\n";
            co_return;
        }
        std::cout << "Pong\n";
    }
}

task<void> server(boost::asio::io_context &context)
{
    Acceptor acceptor{context};
    boost::asio::ip::tcp::endpoint ep{boost::asio::ip::make_address_v4("127.0.0.1"), 4242};
    acceptor.open(ep.protocol());
    acceptor.bind(ep);
    acceptor.listen();

    while (true)
    {
        auto &&[ec, client] = co_await async_accept(context, acceptor);
        if (ec)
        {
            std::cerr << "Accept error: " << ec.message() << "\n";
        }
        else
        {
            session(std::move(client));
        }
    }
}

int main()
{
    boost::asio::io_context context;

    server(context);

    context.run();
}