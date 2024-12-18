#include "ServerCore.hpp"
#include <csignal>
#include <cstdlib>
#include <iostream>

static Server *serverInstance = nullptr;

void signalHandler(int signum) {
    if (serverInstance) {
        std::cout << "\nSignal d'arrêt reçu :'(. Arrêt du serveur... \n\n"
                  << std::endl;
        serverInstance->stop();
    }
}

int main() {
    try {
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);

        ECS ecs;
        Server server;
        serverInstance = &server;

        std::cout << "Attention!!! \nDémarrage du serveur R-Type...\n"
                  << std::endl;

        server.start();

        std::cout << "===============================\n" << std::endl;
        std::cout << "\n... Serveur arrêté avec succès. Bien joué "
                     "!\n\n\n\n\nN'hésite pas a rejoindre Arts&Crafts ;)"
                  << std::endl;
        return 0;

    } catch (const std::exception &e) {
        std::cerr << "Aie aie aie... \nServer error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
