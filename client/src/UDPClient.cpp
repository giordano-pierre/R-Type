#include "UDPClient.hpp"

void UDPClient::operator()(ECS &ecs, const RequestEvent &req_event) {
    std::cout << "send" << std::endl;

    std::vector<uint8_t> bson_data =
        json::to_bson({{"client_uuid", uuid_},
                       {"action_id", (int)req_event.action},
                       {"payload", req_event.payload}});
    uint32_t message_size = static_cast<uint32_t>(bson_data.size());
    uint32_t network_size = htonl(message_size);

    std::vector<uint8_t> buffer;
    buffer.resize(sizeof(network_size) + bson_data.size());

    std::memcpy(buffer.data(), &network_size, sizeof(network_size));

    std::memcpy(buffer.data() + sizeof(network_size), bson_data.data(),
                bson_data.size());

    socket_.async_send_to(
        boost::asio::buffer(buffer), server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes) {
            std::cout << "bytes sent: " << bytes << std::endl;
            if (ec) {
                std::cerr << "send error: " << ec.message() << std::endl;
            }
            start_receive();
        });
}

void UDPClient::start_receive() {
    std::cout << "start_receive" << std::endl;
    socket_.async_receive_from(
        boost::asio::buffer(buffer_), server_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handle_receive(bytes_recvd);
            } else {
                std::cerr << "start_receive error: " << ec.message()
                          << std::endl;
                start_receive();
            }
        });
}

void UDPClient::handle_receive(std::size_t bytes_recvd) {
    std::cout << "handle_receive" << std::endl;

    try {
        if (bytes_recvd < sizeof(uint32_t)) {
            throw std::runtime_error(
                "Received data is too small to include size header");
        }

        uint32_t message_size = 0;
        std::memcpy(&message_size, buffer_.data(), sizeof(uint32_t));
        message_size = ntohl(message_size);

        if (bytes_recvd - sizeof(uint32_t) != message_size) {
            throw std::runtime_error(
                "Mismatch between declared and actual message size");
        }

        std::vector<uint8_t> bson_data(buffer_.data() + sizeof(uint32_t),
                                       buffer_.data() + sizeof(uint32_t) +
                                           message_size);

        json received_json = json::from_bson(bson_data);

        std::cout << "Received: " << received_json.dump() << std::endl;
        parse_request(received_json);

        start_receive();
    } catch (std::exception &e) {
        std::cerr << "Error handling receive: " << e.what() << std::endl;
        start_receive();
    }
}

void UDPClient::parse_request(const json &parsed_json) {
    try {
        NetworkActions action_id =
            parsed_json.at("action_id").get<NetworkActions>();
        json payload = parsed_json.at("payload");

        std::cout << "Action ID: " << action_id << std::endl;
        std::cout << "Payload: " << payload.dump() << std::endl;
        if (action_id == NetworkActions::SEND_UUID && uuid_.empty()) {
            try {
                uuid_ = payload["client_uuid"];
                std::cout << "UUID set to: " << uuid_ << std::endl;
                ecs_.post<RequestEvent>({NetworkActions::ENVOI_CLIENT,
                                         {{"value", "je deteste vigneau"}}});
            } catch (const std::exception &e) {
                std::cerr << "Parsing uuid failed : " << e.what() << std::endl;
            }
        } else {
            ecs_.post<ReceiveEvent>({action_id, payload});
        }
    } catch (const std::exception &e) {
        std::cerr << "Error parsing message: " << e.what() << std::endl;
    }
}
