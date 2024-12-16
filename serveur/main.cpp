#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"
#include "server_header.h"

int main() {
  try {
    Server server;
    server.run();
  } catch (const std::exception &e) {
    std::cerr << "Server error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}