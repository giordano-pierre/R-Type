#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"
#include "server_header.h"

class Server {
private:
  rtype::systems::GameLogicSystem gameLogicSystem;
  float deltaTime;

public:
  void run();
  void update();
}
