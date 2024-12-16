#include "ServerCore.hpp"

Server::Server(ECS &ecs)
    : gameLogicSystem(rtype::systems::GameLogicSystem(ecs)) {}

void Server::run() {
  while (true) {
    update();
  }
}

void Server::update() { gameLogicSystem.update(deltaTime); }
