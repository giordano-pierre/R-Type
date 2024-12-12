#include "UDPServer.hpp"

void UDPServer::start_receive()
{
    std::cout << "start_receive" << std::endl;
    socket_.async_receive_from(
    boost::asio::buffer(buffer_), remote_endpoint_,
    [this](boost::system::error_code ec, std::size_t bytes_recvd) {
        std::cout << "bytes received : " << bytes_recvd << std::endl;
        if (!ec && bytes_recvd > 0) {
            handle_receive(bytes_recvd);
        } else {
            std::cerr << ec << std::endl;
            start_receive();
        }
    });
}

void UDPServer::handle_receive(std::size_t bytes_recvd)
{
    std::cout << "handle_receive" << std::endl;
    std::string received_message(buffer_.data(), bytes_recvd);
    try {
        if (received_message == "connection") {
            std::string new_uuid = get_new_uuid();
            std::cout << "New client with uuid = " << new_uuid << std::endl;
            clients_endpoint_[new_uuid] = remote_endpoint_;
            start_send(new_uuid, new_uuid);
        } else {
        // json received_json = json::parse(received_message);
        //send to the other class
        std::cout << "Received : " << received_message << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error handling receive: " << e.what() << std::endl;
    }
    start_receive();
}

void UDPServer::start_send(const std::string &client_id, const std::string &message)
{
    std::cout << "start_send" << std::endl;
    if (clients_endpoint_.find(client_id) == clients_endpoint_.end()) {
        std::cerr << "[NETWORK] client id " << client_id << " not in the database" << std::endl;
        start_receive();
        return;
    }
    socket_.async_send_to(
        boost::asio::buffer(message), clients_endpoint_[client_id],
        [this](boost::system::error_code, std::size_t ) {
            start_receive();
        });
}

std::string UDPServer::get_new_uuid()
{
    return boost::uuids::to_string(uuid_generator_());
}

