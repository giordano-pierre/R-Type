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

void UDPServer::parse_request(const std::string& received_message)
{
   try {
            json parsed_json = json::parse(received_message);

            std::string client_uuid = parsed_json.at("client_uuid").get<std::string>();
            int action_id = parsed_json.at("action_id").get<int>();
            json payload = parsed_json.at("payload");

            std::cout << "Client UUID: " << client_uuid << std::endl;
            std::cout << "Action ID: " << action_id << std::endl;
            std::cout << "Payload: " << payload.dump() << std::endl;

            // handle_action(client_uuid, action_id, payload);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing message: " << e.what() << std::endl;
        }
}

void UDPServer::handle_receive(std::size_t bytes_recvd) {
    std::cout << "handle_receive" << std::endl;

    try {
        if (bytes_recvd < sizeof(uint32_t)) {
            throw std::runtime_error("Received data is too small to include size header");
        }

        uint32_t message_size = 0;
        std::memcpy(&message_size, buffer_.data(), sizeof(uint32_t));
        message_size = ntohl(message_size);
        if (bytes_recvd - sizeof(uint32_t) != message_size) {
            throw std::runtime_error("Mismatch between declared and actual message size");
        }

        std::string received_message(buffer_.data() + sizeof(uint32_t), message_size);

        std::cout << "RECEIVE [" << received_message << "]" << std::endl;

        if (received_message == "\"connection\"") {
            std::string new_uuid = get_new_uuid();
            std::cout << "New client with uuid = " << new_uuid << std::endl;
            clients_endpoint_[new_uuid] = remote_endpoint_;

            json response_json = {{"client_uuid", new_uuid}};
            start_send(new_uuid, response_json);
        } else {
            parse_request(received_message);
        }
    } catch (std::exception& e) {
        std::cerr << "Error handling receive: " << e.what() << std::endl;
    }
    start_receive();
}


void UDPServer::start_send(const std::string& client_id, const json& message_json) {
        std::cout << "start_send_with_size" << std::endl;

        std::string message = message_json.dump();

        uint32_t message_size = static_cast<uint32_t>(message.size());

        std::vector<uint8_t> buffer;
        buffer.resize(sizeof(message_size) + message_size);

        uint32_t network_size = htonl(message_size);
        std::memcpy(buffer.data(), &network_size, sizeof(network_size));

        std::memcpy(buffer.data() + sizeof(network_size), message.data(), message_size);

        if (clients_endpoint_.find(client_id) == clients_endpoint_.end()) {
            std::cerr << "[NETWORK] client id " << client_id << " not in the database" << std::endl;
            return;
        }

        socket_.async_send_to(
            boost::asio::buffer(buffer), clients_endpoint_[client_id],
            [this](boost::system::error_code, std::size_t) {
                start_receive();
            });
    }

std::string UDPServer::get_new_uuid()
{
    return boost::uuids::to_string(uuid_generator_());
}
