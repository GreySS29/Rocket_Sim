#include "../include/Panel/Server.h"
#include <iostream>
#include <sstream>

RocketServer::RocketServer(unsigned short port, CommandHandler handler)
    : acceptor_(io_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , onCommand_(std::move(handler))
{}

RocketServer::~RocketServer() {
    stop();
}

void RocketServer::start() {
    if (running_) return;
    running_ = true;
    acceptThread_ = std::thread(&RocketServer::acceptLoop, this);
    std::cout << "Server listening on port 5555\n";
}

void RocketServer::stop() {
    if (!running_) return;
    running_ = false;
    io_.stop();
    if (acceptThread_.joinable()) acceptThread_.join();
}

void RocketServer::acceptLoop() {
    while (running_) {
        try {
            boost::asio::ip::tcp::socket socket(io_);
            acceptor_.accept(socket);
            std::thread(&RocketServer::sessionThread, this, std::move(socket)).detach();
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Accept error: " << e.what() << "\n";
            }
        }
    }
}

void RocketServer::sessionThread(boost::asio::ip::tcp::socket socket) {
    try {
        boost::asio::streambuf buffer;
        std::istream is(&buffer);

        while (running_ && socket.is_open()) {
            // Read until newline
            auto n = boost::asio::read_until(socket, buffer, "\n");
            if (n == 0) break;

            std::string line;
            std::getline(is, line);
            if (line.empty()) continue;

            if (onCommand_) {
                onCommand_(line);
            }

            // Push to queue for main loop
            {
                std::lock_guard<std::mutex> lock(queueMutex_);
                cmdQueue_.push(line);
            }
        }
    } catch (const std::exception&) {
        // Client disconnected or error; just exit thread
    }
}

bool RocketServer::pollCommand(std::string& outCmd) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    if (cmdQueue_.empty()) return false;
    outCmd = std::move(cmdQueue_.front());
    cmdQueue_.pop();
    return true;
}