#include "ServerCore.hpp"

Server::run() {
    while (true) {
        update();
    }
}

Server::update() {
    gameLogicSystem.update(deltaTime);
}
