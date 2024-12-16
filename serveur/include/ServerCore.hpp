#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"

class Server {
private:
  rtype::systems::GameLogicSystem gameLogicSystem;
  float deltaTime;

public:
  Server(ECS &ecs);
  ~Server() = default;
  void run();
  void update();
};
