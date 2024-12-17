#pragma once

#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <array>
#include <thread>
#include <map>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ECS/ECS.hpp"
#include "RequestEvent.hpp"
#include "ReceiveEvent.hpp"
#include "NetworkActions.hpp"

using boost::asio::ip::udp;
using json = nlohmann::json;

class UDPServer {
public:
    UDPServer(ECS &ecs, const boost::asio::ip::port_type &port)
        : ecs_(ecs), io_context_(), socket_(io_context_, udp::endpoint(udp::v4(), port)),
        clients_endpoint_(), buffer_(), port_(port) {

        std::cout << "Server running on port: " << port_ << std::endl;

        context_thread_ = std::thread([this]() {
            try {
                start_receive();
                io_context_.run();
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        });
    }

    ~UDPServer() {
        if (!io_context_.stopped())
            io_context_.stop();
        context_thread_.join();
    }

    void operator()(ECS &ecs, const RequestEvent &req_event);
    // void start_send(const std::string& client_id, const json& message_json);

private:
    ECS &ecs_;
    boost::uuids::random_generator uuid_generator_;
    boost::asio::io_context io_context_;
    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::map<std::string, udp::endpoint> clients_endpoint_;
    std::array<char, 1024> buffer_;
    unsigned short port_;
    std::thread context_thread_;

    void start_receive();
    void handle_receive(std::size_t bytes_recvd);
    std::string get_new_uuid();
    void parse_request(const json& parsed_json);

};
