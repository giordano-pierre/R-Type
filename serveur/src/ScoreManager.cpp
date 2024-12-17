#include "ScoreManager.hpp"
#include <stdexcept>

namespace rtype {
namespace systems {

void ScoreManager::registerPlayer(Entity entity) {
  if (scores.find(entity) != scores.end()) {
    return;
  }
  scores[entity] = PlayerScore(0, 0, 0, 0.0f);
}

void ScoreManager::removePlayer(Entity entity) { scores.erase(entity); }

void ScoreManager::updateScore(Entity entity, int points) {
  if (!hasPlayer(entity)) {
    registerPlayer(entity);
  }
  scores[entity].score += points;
  if (scores[entity].score < 0) {
    scores[entity].score = 0;
  }
}

void ScoreManager::addKill(Entity entity) {
  if (hasPlayer(entity)) {
    scores[entity].kills++;
    updateScore(entity, KILL_BONUS);
  }
}

void ScoreManager::addDeath(Entity entity) {
  if (hasPlayer(entity)) {
    scores[entity].deaths++;
    updateScore(entity, DEATH_PENALTY);
  }
}

void ScoreManager::updateTimeBonus(Entity entity, float gameTime) {
  if (!hasPlayer(entity)) {
    return;
  }

  auto &playerScore = scores[entity];
  float oldTime = playerScore.survivalTime;
  playerScore.survivalTime = gameTime;

  int oldIntervals = static_cast<int>(oldTime / TIME_BONUS_INTERVAL);
  int newIntervals = static_cast<int>(gameTime / TIME_BONUS_INTERVAL);

  if (newIntervals > oldIntervals) {
    updateScore(entity, TIME_BONUS_POINTS);
  }
}

const PlayerScore &ScoreManager::getPlayerScore(Entity entity) const {
  auto it = scores.find(entity);
  if (it == scores.end()) {
    throw std::runtime_error("Player not found");
  }
  return it->second;
}

bool ScoreManager::hasPlayer(Entity entity) const {
  return scores.find(entity) != scores.end();
}

} // namespace systems
} // namespace rtype