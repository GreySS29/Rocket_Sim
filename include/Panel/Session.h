#pragma once
#include <boost/asio.hpp>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
//#include <atomic>
//#include <functional>
#include "Session.h"


struct Session {
    boost::asio::ip::tcp::socket socket;
    bool telemetryClient{true};

    std::mutex writeMutex;
    std::condition_variable writeCv;
    std::queue<std::string> writeQueue;
    std::atomic<bool> alive{true};
    std::thread writerThread;

    explicit Session(boost::asio::ip::tcp::socket s) : socket(std::move(s)) {}

    void startWriter() {
        writerThread = std::thread([this] {
            while (alive) {
                std::string msg;
                {
                    std::unique_lock<std::mutex> lock(writeMutex);
                    writeCv.wait(lock, [this] { return !writeQueue.empty() || !alive; });
                    if (!alive && writeQueue.empty()) return;
                    msg = std::move(writeQueue.front());
                    writeQueue.pop();
                }
                try {
                    boost::asio::write(socket, boost::asio::buffer(msg));
                } catch (const std::exception& e) {
                    std::cerr << "[telemetry] write failed: " << e.what() << "\n";
                    boost::system::error_code ec;
                    socket.close(ec);
                    alive = false;
                    return;
                }
            }
        });
    }

    void enqueue(const std::string& msg) {
        {
            std::lock_guard<std::mutex> lock(writeMutex);
            if (writeQueue.size() > 50) return; // защита от неограниченного роста очереди у мёртвого клиента
            writeQueue.push(msg);
        }
        writeCv.notify_one();
    }

    ~Session() {
        alive = false;
        writeCv.notify_one();
        if (writerThread.joinable()) writerThread.join();
    }
};