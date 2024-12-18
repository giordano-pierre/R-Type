#include "CollisionSystem.hpp"
#include "GameLogicSystem.hpp"
#include "LevelManagement.hpp"
#include "MovementSystem.hpp"
#include "ScoreManager.hpp"
#include <chrono>
#include <thread>

class Server {
  private:
    ECS ecs;
    rtype::systems::GameLogicSystem gameLogicSystem;
    rtype::systems::MovementSys movementSystem;
    rtype::systems::CollisionSys collisionSystem;
    rtype::systems::LevelManager levelManager;

    bool isRunning;
    float deltaTime;
    std::chrono::steady_clock::time_point lastUpdate;
    static constexpr int TICKS_PER_SECOND = 60;
    static constexpr float TICK_DURATION = 1.0f / TICKS_PER_SECOND;

    void run();
    void updateDeltaTime();
    void update();
    void processNetworkEvents();
    void handleCollisions();
    void reset();

  public:
    Server(ECS _ecs);
    ~Server();

    void start();
    void stop();
    void queueCommand(std::function<void()> command);
};
