#include "ECS/ECS.hpp"
#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"
#include "ServerCore.hpp"
#include "ServerHandlerSystem.hpp"
#include "UDPServer.hpp"
#include <iostream>

int main() {
    try {
        ECS ecs;
        ServerHandlerSystem server_handler;
        UDPServer server(ecs, 4242);
        ecs.register_event<RequestEvent>();
        ecs.register_event<ReceiveEvent>();
        ecs.subscribe<RequestEvent>(server);
        ecs.subscribe<ReceiveEvent>(server_handler);
        while (true) {
            if (!ecs.empty()) {
                auto &callback = ecs.front();
                callback();
                ecs.pop_front();
            }
        };
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

// int main() {
//   try {
//     ECS ecs;
//     Server server(ecs);
//     server.run();
//   } catch (const std::exception &e) {
//     std::cerr << "Server error: " << e.what() << std::endl;
//     return 1;
//   }
//   return 0;
// }