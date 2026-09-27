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
        
        std::string line;
        bool identified = false;

        for (int attempts = 0; attempts < 5 && !identified; ++attempts) {
            if (boost::asio::read_until(session->socket, buffer, "\n") == 0) break;
            std::getline(is, line);
            trimLineEnding(line);

            if (line.empty()) continue; // пропускаем пустые строки, пробуем снова

            if (line == "PANEL") {
                session->telemetryClient = false;
                identified = true;
            } else if (line == "TELEMETRY") {
                session->telemetryClient = true;
                identified = true;
            } else {
                std::cerr << "Unknown identifier, len=" << line.size() << ": [" << line << "]\n";
                boost::system::error_code ec;
                session->socket.close(ec);
                return;
            }
        }

        if (!identified) {
            boost::system::error_code ec;
            session->socket.close(ec);
            return;
        }

        {
    std::lock_guard<std::mutex> lock(sessionsMutex_);
    sessions_.push_back(session);
    }
    session->startWriter(); 

    if (session->telemetryClient) {
        // Только детектируем дисконнект, ничего не парсим и не кладём в очередь
        while (running_ && session->socket.is_open()) {
            char discard[256];
            boost::system::error_code ec;
            size_t n = session->socket.read_some(boost::asio::buffer(discard), ec);
            if (ec || n == 0) break; // клиент закрыл соединение или ошибка
            // данные просто игнорируем
        }
    } else {
        // PANEL — читаем и парсим команды построчно
        while (running_ && session->socket.is_open()) {
            auto n = boost::asio::read_until(session->socket, buffer, "\n");
            if (n == 0) break;

            std::string line;
            std::getline(is, line);
            trimLineEnding(line);
            if (line.empty()) continue;

            if (onCommand_) {
                onCommand_(line);
            }
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
        return s == session; });
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
        session->enqueue(msg); 
    }
}

