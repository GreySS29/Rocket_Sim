#include "../include/Panel/Server.h"
#include <iostream>
#include <sstream>

Server::Server(unsigned short port, CommandHandler handler)
    : acceptor_(io_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    , onCommand_(std::move(handler))
{}

Server::~Server() {
    stop();
}

void Server::start() {
    if (running_) return;
    running_ = true;
    acceptThread_ = std::thread(&Server::acceptLoop, this);
    std::cout << "Server listening on port 5555\n";
}

void Server::stop() {
    if (!running_) return;
    running_ = false;
    io_.stop();
    if (acceptThread_.joinable()) acceptThread_.join();
}

void Server::acceptLoop() {
    while (running_) {
        try {
            boost::asio::ip::tcp::socket socket(io_);
            acceptor_.accept(socket);
            std::thread(&Server::sessionThread, this, std::move(socket)).detach();
        } catch (const std::exception& e) {
            if (running_) {
                std::cerr << "Accept error: " << e.what() << "\n";
            }
        }
    }
}

void Server::sessionThread(boost::asio::ip::tcp::socket socket) {
    
    
    auto session = std::make_shared<Session>(std::move(socket));
    

    try {
        boost::asio::streambuf buffer;
        std::istream is(&buffer);

        if (boost::asio::read_until(session->socket, buffer , "\n")>0)
        {
            std::string line;
            std::getline(is, line);
            if (line == "PANEL") {
                session->telemetryClient = false;
            }
        }

        {
        std::lock_guard<std::mutex>lock(sessionsMutex_);
        sessions_.push_back(session);
        }

        //reading commands 
        while (running_ && session->socket.is_open()) {
           
            auto n = boost::asio::read_until(session->socket, buffer, "\n");
            if (n == 0) break;

            std::string line;
            std::getline(is, line);
            if (line.empty()) continue;

            if(!session->telemetryClient){
                 if (onCommand_) {
                onCommand_(line);
            }
            }
           
            {
            std::lock_guard<std::mutex> lock(queueMutex_);
            cmdQueue_.push(line);
            }
        }
    } catch (const boost::system::system_error& e) {
    if (e.code() == boost::asio::error::eof) {
        std::cerr << "Client disconnected (EOF)\n";
    } else {
        std::cerr << "Socket error: " << e.what() << " (code: " << e.code() << ")\n";
    }
    } catch (const std::exception& e) {
        std::cerr << "Client disconnected or error: " << e.what() << "\n";
    }

    {
    std::lock_guard<std::mutex> lock(sessionsMutex_); // delete session from vector
    std::erase_if(sessions_, [&session](const std::shared_ptr<Session>& s) {
    return s == session;
    });
}
}

bool Server::pollCommand(std::string& outCmd) {
    std::lock_guard<std::mutex> lock(queueMutex_);
    if (cmdQueue_.empty()) return false;
    outCmd = std::move(cmdQueue_.front());
    cmdQueue_.pop();
    return true;
}

void Server::sendTelemetry(ExDataGUI& data) {
    std::string msg = data.serializeExDataGUI();

    std::vector<std::shared_ptr<Session>> currentSessions;
    {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        currentSessions = sessions_;
    }

    for (auto& session : currentSessions) {
        if (!session->telemetryClient) continue;
        if (!session->socket.is_open()) continue;

        std::lock_guard<std::mutex> wlock(session->writeMutex);
        try {
           size_t written = boost::asio::write(session->socket, boost::asio::buffer(msg));
            std::cerr << "[telemetry] sent " << written << " bytes: " << msg << "\n"; // temp
        } catch (const std::exception& e) {
            std::cerr << "disconnect: " << e.what() << "\n";
        }
    }
}