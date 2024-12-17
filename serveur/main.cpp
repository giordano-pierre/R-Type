#include "ServerCore.hpp"
#include <csignal>
#include <cstdlib>
#include <iostream>

static Server *serverInstance = nullptr;

void signalHandler(int signum) {
  if (serverInstance) {
    std::cout << "\nSignal d'arrêt reçu. Arrêt du serveur..." << std::endl;
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
    server.start();
  } catch (const std::exception &e) {
    std::cerr << "Server error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
