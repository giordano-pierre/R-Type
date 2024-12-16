#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"
#include "ServerCore.hpp"
#include <iostream>

int main() {
  try {
    ECS ecs;
    Server server(ecs);
    server.run();
  } catch (const std::exception &e) {
    std::cerr << "Server error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}