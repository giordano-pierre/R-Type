/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LevelLoader
*/

#pragma once

#include <filesystem>
#include <iostream>
#include <map>

namespace rtype::server {

class LevelLoader {
  public:
    LevelLoader();
    ~LevelLoader() = default;

    void reset(void);
    const std::map<int, std::string> &getLevels(void);
    std::string getOneLevel(int);

    std::map<int, std::string> _map;
};

} // namespace rtype::server
