#include "UDPClient.hpp"

void UDPClient::send(const std::string &message)
{
    std::cout << "send" << std::endl;
    socket_.async_send_to(
        boost::asio::buffer(message), server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes) {
            std::cout << "bytes sended : " << bytes << std::endl;
            if (ec) {
                std::cerr << "send error " << ec << std::endl;
            }
            start_receive();
        });
}

void UDPClient::start_receive()
{
    std::cout << "Start reveive" << std::endl;
    socket_.async_receive_from(
        boost::asio::buffer(buffer_), server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handle_receive(bytes_recvd);
            } else {
                std::cerr << "start_receive error " << ec << std::endl;
                start_receive();
            }
        });
}

void UDPClient::handle_receive(std::size_t bytes_recvd)
{
    std::cout << "handle_reive" << std::endl;
    std::string received_message(buffer_.data(), bytes_recvd);
    try {
        if (uuid_.empty()) {
            uuid_ = received_message;
            std::cout << "UUID set to " << uuid_ << std::endl;
            start_receive();
            return;
        }
        std::cout << "Received : " << received_message << std::endl;
        start_receive();
    } catch (std::exception& e) {
        std::cerr << "Error handling receive: " << e.what() << std::endl;
    }
}
