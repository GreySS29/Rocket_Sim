#pragma once
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <functional>
#include "../GUI/ExDataGUI.h"
#include "Session.h"

class Server {
public:
    using CommandHandler = std::function<void(const std::string&)>;

    explicit Server(unsigned short port, CommandHandler handler);
    ~Server();

    void start();
    void stop();

    // Called by main loop to consume commands
    bool pollCommand(std::string& outCmd);
    void sendTelemetry(ExDataGUI& data);

    static void trimLineEnding(std::string& s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
        s.pop_back();
    }
    }


    

private:
    std::queue<std::string> cmdQueue_;
    std::mutex queueMutex_;
    std::vector<std::shared_ptr<Session>> sessions_;
    std::mutex sessionsMutex_;

    boost::asio::io_context io_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::thread acceptThread_;
    std::atomic<bool> running_{false};

    CommandHandler onCommand_;

    void acceptLoop();
    void sessionThread(boost::asio::ip::tcp::socket socket);

 
};