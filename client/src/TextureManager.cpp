/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TextureManager
*/

#include "TextureManager.hpp"

namespace Rtype::Client {

std::shared_ptr<sf::Texture> TextureManager::getTexture(std::string path) {
  if (_map.find(path) == _map.end()) {
    sf::Texture tmp = sf::Texture();
    tmp.loadFromFile(path);
    std::shared_ptr<sf::Texture> elem = std::make_shared<sf::Texture>(tmp);
    _map.insert({path, elem});
  }
  return _map.find(path)->second;
}

} // namespace Rtype::Client
