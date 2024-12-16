#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"

class Server {
private:
  rtype::systems::GameLogicSystem gameLogicSystem;
  float deltaTime;

public:
  void run();
  void update();
};
