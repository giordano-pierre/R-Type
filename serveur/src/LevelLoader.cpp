/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LevelLoader
*/

#include "LevelLoader.hpp"

namespace rtype::server {

LevelLoader::LevelLoader() { this->reset(); }

void LevelLoader::reset(void) {
    _map.clear();
    std::string dossier = "level";
    int cmpt = 0;

    try {
        if (std::filesystem::exists(dossier) &&
            std::filesystem::is_directory(dossier)) {
            for (const auto &entry :
                 std::filesystem::directory_iterator(dossier)) {
                cmpt += 1;
                _map.insert(
                    {cmpt, "level/" + entry.path().filename().string()});
                std::cout << entry.path().filename().string() << std::endl;
            }
        } else {
            std::cerr
                << "Le chemin spécifié n'est pas un dossier ou n'existe pas."
                << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
}

const std::map<int, std::string> &LevelLoader::getLevels(void) { reset(); return _map; }

std::string LevelLoader::getOneLevel(int nb) {
    if (_map.find(nb) != _map.end())
        return _map.find(nb)->second;
    return "";
}

} // namespace rtype::server
