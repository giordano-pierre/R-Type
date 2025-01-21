/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Singleton.hpp
*/

#pragma once

#include "Components.hpp"
#include <stdexcept>
#include <vector>

class SpawnQueue {
  public:
    void add(const rtype::server::EnemyAI::BehaviorType &behavior) {
        _spawnQueue.push_back(behavior);
    }

    rtype::server::EnemyAI::BehaviorType pop() {
        if (_spawnQueue.empty()) {
            throw std::runtime_error("SpawnQueue is empty. Cannot pop.");
        }
        rtype::server::EnemyAI::BehaviorType front = _spawnQueue.front();
        _spawnQueue.erase(_spawnQueue.begin());
        return front;
    }

    bool isEmpty() const { return _spawnQueue.empty(); }

  private:
    std::vector<rtype::server::EnemyAI::BehaviorType> _spawnQueue;
};
