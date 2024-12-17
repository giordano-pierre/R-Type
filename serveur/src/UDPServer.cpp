#include "UDPServer.hpp"

void UDPServer::start_receive()
{
    std::cout << "start_receive" << std::endl;
    socket_.async_receive_from(
        boost::asio::buffer(buffer_), remote_endpoint_,
        [this](boost::system::error_code ec, std::size_t bytes_recvd)
        {
            std::cout << "bytes received : " << bytes_recvd << std::endl;
            if (!ec && bytes_recvd > 0)
            {
                handle_receive(bytes_recvd);
            }
            else
            {
                std::cerr << ec << std::endl;
                start_receive();
            }
        });
}

void UDPServer::parse_request(const json &parsed_json)
{
    try
    {
        std::string client_uuid = parsed_json.at("client_uuid").get<std::string>();
        NetworkActions action_id = parsed_json.at("action_id").get<NetworkActions>();
        json payload = parsed_json.at("payload");

        std::cout << "Client UUID: " << client_uuid << std::endl;
        std::cout << "Action ID: " << action_id << std::endl;
        std::cout << "Payload: " << payload.dump() << std::endl;
        ecs_.post<ReceiveEvent>({action_id, payload, client_uuid});
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing message: " << e.what() << std::endl;
    }
}

void UDPServer::handle_receive(std::size_t bytes_recvd)
{
    std::cout << "handle_receive" << std::endl;

    try
    {
        if (bytes_recvd < sizeof(uint32_t))
        {
            throw std::runtime_error("Received data is too small to include size header");
        }

        uint32_t message_size = 0;
        std::memcpy(&message_size, buffer_.data(), sizeof(uint32_t));
        message_size = ntohl(message_size);
        if (bytes_recvd - sizeof(uint32_t) != message_size)
        {
            throw std::runtime_error("Mismatch between declared and actual message size");
        }

        std::vector<uint8_t> bson_data(buffer_.data() + sizeof(uint32_t),
                                       buffer_.data() + sizeof(uint32_t) + message_size);

        json received_json = json::from_bson(bson_data);
        std::cout << "RECEIVE [" << received_json.dump() << "]" << std::endl;

        if (received_json.at("action_id").get<NetworkActions>() == NetworkActions::CONNECT)
        {
            std::string new_uuid = get_new_uuid();
            std::cout << "New client with uuid = " << new_uuid << std::endl;
            clients_endpoint_[new_uuid] = remote_endpoint_;

            json response_json = {{"client_uuid", new_uuid}};
            ecs_.post<ReceiveEvent>({NetworkActions::NEW_CLIENT, response_json, new_uuid});
        }
        else
        {
            parse_request(received_json);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error handling receive: " << e.what() << std::endl;
    }
    start_receive();
}

void UDPServer::operator()(ECS &ecs, const RequestEvent &req_event)
{
    std::cout << "start_send" << std::endl;

    std::vector<uint8_t> bson_data = json::to_bson({{"action_id", (int)req_event.action}, {"payload", req_event.payload}});
    uint32_t message_size = static_cast<uint32_t>(bson_data.size());
    uint32_t network_size = htonl(message_size);

    std::vector<uint8_t> buffer;
    buffer.resize(sizeof(network_size) + bson_data.size());

    std::memcpy(buffer.data(), &network_size, sizeof(network_size));

    std::memcpy(buffer.data() + sizeof(network_size), bson_data.data(), bson_data.size());
    if (req_event.receiver_uuid.length() != 0) {
        if (clients_endpoint_.find(req_event.receiver_uuid) == clients_endpoint_.end())
        {
            std::cerr << "[NETWORK] client id " << req_event.receiver_uuid << " not in the database" << std::endl;
            return;
        }
        socket_.async_send_to(
            boost::asio::buffer(buffer), clients_endpoint_[req_event.receiver_uuid],
            [this](boost::system::error_code, std::size_t)
            {
                start_receive();
            });
    }
    // ADD else : send the message to everyone (loop on clients_endpoint_)
}

std::string UDPServer::get_new_uuid()
{
    return boost::uuids::to_string(uuid_generator_());
}
