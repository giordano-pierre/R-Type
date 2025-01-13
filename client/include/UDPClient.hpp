/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDPClient
*/

#pragma once

#include "ECS/ECS.hpp"
#include "events/ReceiveEvent.hpp"
#include "events/RequestEvent.hpp"
#include "protocol.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

using boost::asio::ip::udp;
using json = nlohmann::json;

class UDPClient {
  public:
    UDPClient(ECS &ecs, const std::string &host, const std::string &port)
        : ecs_(ecs), io_context_(), socket_(io_context_),
          server_endpoint_(*udp::resolver(io_context_)
                                .resolve(udp::v4(), host, port)
                                .begin()),
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

    void operator()(ECS &ecs, const RequestEvent &req_event);
    bool isConnected(void);
    // void send(const json& message_json);

  private:
    ECS &ecs_;
    boost::asio::io_context io_context_;
    udp::socket socket_;
    udp::endpoint server_endpoint_;
    std::array<char, 1024> buffer_;
    std::string uuid_;
    std::thread context_thread_;

    void start_receive();

    void handle_receive(std::size_t bytes_recvd);
    void parse_request(const json &parsed_json);
};
