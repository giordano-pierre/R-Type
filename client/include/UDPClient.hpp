#pragma once

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::udp;
using json = nlohmann::json;

class UDPClient {
public:
    UDPClient(const std::string& host, const std::string &port)
        : io_context_(), socket_(io_context_),
        server_endpoint_(*udp::resolver(io_context_).resolve(udp::v4(), host, port).begin()),
            buffer_{}, uuid_("") {

        try {
            socket_.open(udp::v4());
            std::cout << "Connected to " << host << ":" << port << std::endl;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        context_thread_ = std::thread([this]() {
            start_receive();
            io_context_.run();
        });
    }

    ~UDPClient() {
        if (!io_context_.stopped())
            io_context_.stop();
        context_thread_.join();
    }

    void send(const json& message_json);

private:
    boost::asio::io_context io_context_;
    udp::socket socket_;
    udp::endpoint server_endpoint_;
    std::array<char, 1024> buffer_;
    std::string uuid_;
    std::thread context_thread_;

    void start_receive();

    void handle_receive(std::size_t bytes_recvd);
    void parse_request(const std::string& received_message);
};
