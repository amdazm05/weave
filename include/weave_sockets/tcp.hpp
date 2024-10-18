#ifndef _WEAVE_TCP
#define _WEAVE_TCP

#include <string_view>
#include <asio/co_spawn.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/co_spawn.hpp>
#include <asio/signal_set.hpp>
#include <asio/detached.hpp>
#include <asio/write.hpp>
#include <spdlog/spdlog.h>

/******
 * This is TODO item, slowly migrating towards asio
 */

namespace weave_sockets
{
    using asio::ip::tcp;
    using asio::co_spawn;
    using asio::awaitable;
    using asio::detached;
    using asio::use_awaitable;
    namespace this_coro = asio::this_coro;
    // the process of converting a host name to its corresponding IP address
    class tcp_resolver
    {
        public:
            tcp_resolver()=delete;
            tcp_resolver(std::string_view hostname):hostname(hostname)
            {

            }
            ~tcp_resolver()
            {

            }
            std::string_view get_host_name();

        private:
            std::string_view hostname; 

    };
    class tcp_server_t
    {
        public:
            tcp_server_t(size_t threadcount,size_t portnum):io_context(threadcount),portNumber(portnum)
            {
                asio::signal_set signals(io_context,SIGINT,SIGTERM);
                signals.async_wait([&](auto,auto){
                        io_context.stop();
                });
                // A completion token object used to specify that an asynchronous operation is detached.
                co_spawn(io_context,listener(),detached);
                io_context.run();
            }
        private:
            awaitable<void> echo(tcp::socket socket_)
            {
                try{
                    for(;;)
                    {
                        std::size_t byteCount = co_await socket_.async_read_some(asio::buffer(data));
                        co_await async_write(socket_,asio::buffer(data,byteCount),use_awaitable);
                    }
                }
                catch(std::exception & e)
                {
                    spdlog::error("echo_exception : {}",e.what());
                }
            }

            awaitable<void> listener()
            {
                auto executor = co_await this_coro::executor;
                tcp::acceptor acceptor(executor, {tcp::v4(), portNumber});
                for (;;)
                {
                    spdlog::info("Waiting for connection");
                    tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
                    co_spawn(executor, echo(std::move(socket)), detached);
                }
            }
            std::array<char,1024> data;
            uint16_t portNumber;
            //Takes a concurrency ie how many threads to run
            asio::io_context io_context;
    };
    class tcp_client_t
    {
        public:
        private:
    };
}

#endif //_WEAVE_TCP