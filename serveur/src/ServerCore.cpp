#include "ServerCore.hpp"

Server::Server()
    : gameLogicSystem(ecs), levelManager(ecs), isRunning(false),
      deltaTime(0.0f) {}

Server::~Server() {
  if (isRunning) {
    stop();
  }
}

void Server::start() {
  isRunning = true;
  lastUpdate = std::chrono::steady_clock::now();
  run();
}

void Server::stop() { isRunning = false; }

void Server::updateDeltaTime() {
  auto currentTime = std::chrono::steady_clock::now();
  deltaTime = std::chrono::duration<float>(currentTime - lastUpdate).count();
  lastUpdate = currentTime;
}

void Server::update() {
  gameLogicSystem.update(deltaTime);
  processNetworkEvents();
}

void Server::queueCommand(std::function<void()> command) {}

void Server::reset() {}

void Server::handleCollisions() {}

void Server::processNetworkEvents() {}

void Server::run() {
  gameLogicSystem.startGame();

  while (isRunning) {
    auto loopStart = std::chrono::steady_clock::now();

    updateDeltaTime();
    update();

    if (gameLogicSystem.isGameRunning()) {
      if (levelManager.isLevelComplete()) {
        if (levelManager.hasNextLevel()) {
          levelManager.nextLevel();
        } else {
          gameLogicSystem.endGame();
        }
      }
    }

    auto loopEnd = std::chrono::steady_clock::now();
    auto loopDuration =
        std::chrono::duration<float>(loopEnd - loopStart).count();
    if (loopDuration < TICK_DURATION) {
      std::this_thread::sleep_for(
          std::chrono::duration<float>(TICK_DURATION - loopDuration));
    }
  }
}
