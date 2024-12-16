#include "server_header.h"
#include "GameLogicSystem.hpp"
#include "ScoreManager.hpp"
class Server {
private:
    rtype::systems::GameLogicSystem gameLogicSystem;
    float deltaTime;

public:
    void run() {
        while (true) {
            update();
        }
    }

    void update() {
        gameLogicSystem.update(deltaTime);
    }
};