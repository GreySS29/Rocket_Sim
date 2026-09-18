#pragma once
#include <boost/asio.hpp>
#include <string>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <functional>

class RocketServer {
public:
    using CommandHandler = std::function<void(const std::string&)>;

    explicit RocketServer(unsigned short port, CommandHandler handler);
    ~RocketServer();

    void start();
    void stop();

    // Called by main loop to consume commands
    bool pollCommand(std::string& outCmd);

private:
    void acceptLoop();
    void sessionThread(boost::asio::ip::tcp::socket socket);

    boost::asio::io_context io_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::thread acceptThread_;
    std::atomic<bool> running_{false};

    CommandHandler onCommand_;

    std::queue<std::string> cmdQueue_;
    std::mutex queueMutex_;
};