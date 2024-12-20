#pragma once
#include "Components.hpp"
#include "ECS/ECS.hpp"
#include <map>

namespace rtype::server {
namespace systems {

class ScoreManager {
  public:
    ScoreManager() = default;
    ~ScoreManager() = default;

    void registerPlayer(Entity entity);
    void removePlayer(Entity entity);
    void updateScore(Entity entity, int points);
    void addKill(Entity entity);
    void addDeath(Entity entity);
    void updateTimeBonus(Entity entity, float gameTime);

    const PlayerScore &getPlayerScore(Entity entity) const;
    bool hasPlayer(Entity entity) const;
    const std::map<Entity, PlayerScore> &getAllScores() const { return scores; }

  private:
    std::map<Entity, PlayerScore> scores;
    static constexpr int TIME_BONUS_INTERVAL = 30;
    static constexpr int TIME_BONUS_POINTS = 10;
    static constexpr int KILL_BONUS = 100;
    static constexpr int DEATH_PENALTY = -50;
};

} // namespace systems
} // namespace rtype::server