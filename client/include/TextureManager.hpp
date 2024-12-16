/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace Rtype::Client{
    class TextureManager {
        public:
            TextureManager() = default;
            ~TextureManager() = default;

            std::shared_ptr<sf::Texture> getTexture(std::string);

        private:
            std::map<std::string, std::shared_ptr<sf::Texture>> _map;
    };
}
