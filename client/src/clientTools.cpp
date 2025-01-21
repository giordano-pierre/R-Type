/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** clientTools
*/

#include "components/Tag.hpp"
#include <cmath>
#include <iostream>

#include "clientTools.hpp"
#include "ecsObjects.hpp"

namespace rtype::client {

void killMyEntity(ECS &ecs, Entity i) {
    auto tag = ecs.get_components<Tag>()[i].value();
    auto &myConfig = ecs.get_components<Configs>()[0].value();
    auto &SFMLObj = ecs.get_components<SFMLObjects>()[0].value();
    auto &postion = ecs.get_components<Position>()[i].value();
    auto &hitbox = ecs.get_components<Hitbox>()[i].value();
    auto serverSize = myConfig._serverSize;

    if (tag._type >= ENEMY1 && tag._type <= PLAYER) {
        Entity boom1 = ecs.spawn_entity();
        ecs.add_component<Tag>(boom1, {});
        ecs.add_component<Scene>(boom1, {MENU});
        ecs.add_component<Position>(boom1,
                                    {postion._server.x, postion._server.y});
        ecs.add_component<Hitbox>(boom1, hitbox._coefSize);
        ecs.add_component<rtype::client::Drawable>(
            boom1, {SFMLObj._myTextures.getTexture(
                        "assets/images/utils/explosion.png"),
                    {5790, 4500},
                    {1930, 2250},
                    6,
                    2,
                    true});
        ecs.add_component<rtype::client::Sound>(
            boom1, {"assets/audio/explosion2.ogg",
                    rtype::client::SoundState::PLAY_ONCE, 50.0f});
    }
    ecs.kill_entity(i);
}

float computeDist(TupleFloat a, TupleFloat b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void initGeneralInput(
    std::map<UserInput,
             std::pair<sf::Keyboard::Key, std::shared_ptr<std::string>>>
        &inputConfig) {
    if (inputConfig.find(ENTER) == inputConfig.end())
        inputConfig.insert(
            {ENTER,
             {sf::Keyboard::Enter, std::make_shared<std::string>(
                                       convertInput(sf::Keyboard::Enter))}});
    else {
        inputConfig.find(ENTER)->second.first = sf::Keyboard::Enter;
        inputConfig.find(ENTER)->second.second->replace(
            0, inputConfig.find(ENTER)->second.second->size(),
            convertInput(sf::Keyboard::Enter));
    }
    if (inputConfig.find(PAUSE) == inputConfig.end())
        inputConfig.insert(
            {PAUSE,
             {sf::Keyboard::P, std::make_shared<std::string>(
                                   convertInput(sf::Keyboard::Enter))}});
    else {
        inputConfig.find(PAUSE)->second.first = sf::Keyboard::P;
        inputConfig.find(PAUSE)->second.second->replace(
            0, inputConfig.find(PAUSE)->second.second->size(),
            convertInput(sf::Keyboard::P));
    }
    if (inputConfig.find(QUIT) == inputConfig.end())
        inputConfig.insert(
            {QUIT,
             {sf::Keyboard::Escape, std::make_shared<std::string>(
                                        convertInput(sf::Keyboard::Escape))}});
    else {
        inputConfig.find(QUIT)->second.first = sf::Keyboard::Escape;
        inputConfig.find(QUIT)->second.second->replace(
            0, inputConfig.find(QUIT)->second.second->size(),
            convertInput(sf::Keyboard::Escape));
    }
}

void initPlay1Input(
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig) {
    auto &pressed = inputConfig.first;
    auto &released = inputConfig.second;

    if (pressed.find(UP1P) == pressed.end())
        pressed.insert(
            {UP1P,
             {sf::Keyboard::Up,
              std::make_shared<std::string>(convertInput(sf::Keyboard::Up))}});
    else {
        pressed.find(UP1P)->second.first = sf::Keyboard::Up;
        pressed.find(UP1P)->second.second->replace(
            0, pressed.find(UP1P)->second.second->size(),
            convertInput(sf::Keyboard::Up));
    }
    if (pressed.find(DOWN1P) == pressed.end())
        pressed.insert(
            {DOWN1P,
             {sf::Keyboard::Down, std::make_shared<std::string>(
                                      convertInput(sf::Keyboard::Down))}});
    else {
        pressed.find(DOWN1P)->second.first = sf::Keyboard::Down;
        pressed.find(DOWN1P)->second.second->replace(
            0, pressed.find(DOWN1P)->second.second->size(),
            convertInput(sf::Keyboard::Down));
    }
    if (pressed.find(LEFT1P) == pressed.end())
        pressed.insert(
            {LEFT1P,
             {sf::Keyboard::Left, std::make_shared<std::string>(
                                      convertInput(sf::Keyboard::Left))}});
    else {
        pressed.find(LEFT1P)->second.first = sf::Keyboard::Left;
        pressed.find(LEFT1P)->second.second->replace(
            0, pressed.find(LEFT1P)->second.second->size(),
            convertInput(sf::Keyboard::Left));
    }
    if (pressed.find(RIGHT1P) == pressed.end())
        pressed.insert(
            {RIGHT1P,
             {sf::Keyboard::Right, std::make_shared<std::string>(
                                       convertInput(sf::Keyboard::Right))}});
    else {
        pressed.find(RIGHT1P)->second.first = sf::Keyboard::Right;
        pressed.find(RIGHT1P)->second.second->replace(
            0, pressed.find(RIGHT1P)->second.second->size(),
            convertInput(sf::Keyboard::Right));
    }
    released.insert({UP1R, sf::Keyboard::Up});
    released.insert({DOWN1R, sf::Keyboard::Down});
    released.insert({LEFT1R, sf::Keyboard::Left});
    released.insert({RIGHT1R, sf::Keyboard::Right});
    if (pressed.find(SHOOT1) == pressed.end())
        pressed.insert(
            {SHOOT1,
             {sf::Keyboard::Enter, std::make_shared<std::string>(
                                       convertInput(sf::Keyboard::Enter))}});
    else {
        pressed.find(SHOOT1)->second.first = sf::Keyboard::Enter;
        pressed.find(SHOOT1)->second.second->replace(
            0, pressed.find(SHOOT1)->second.second->size(),
            convertInput(sf::Keyboard::Enter));
    }
    if (pressed.find(SUPERSHOOT1) == pressed.end())
        pressed.insert({SUPERSHOOT1,
                        {sf::Keyboard::M, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::M))}});
    else {
        pressed.find(SUPERSHOOT1)->second.first = sf::Keyboard::M;
        pressed.find(SUPERSHOOT1)
            ->second.second->replace(
                0, pressed.find(SUPERSHOOT1)->second.second->size(),
                convertInput(sf::Keyboard::M));
    }
}

void initPlay2Input(
    std::pair<std::map<UserInput, std::pair<sf::Keyboard::Key,
                                            std::shared_ptr<std::string>>>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig) {
    auto &pressed = inputConfig.first;
    auto &released = inputConfig.second;

    if (pressed.find(UP2P) == pressed.end())
        pressed.insert({UP2P,
                        {sf::Keyboard::Z, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::Z))}});
    else {
        pressed.find(UP2P)->second.first = sf::Keyboard::Z;
        pressed.find(UP2P)->second.second->replace(
            0, pressed.find(UP2P)->second.second->size(),
            convertInput(sf::Keyboard::Z));
    }
    if (pressed.find(DOWN2P) == pressed.end())
        pressed.insert({DOWN2P,
                        {sf::Keyboard::S, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::S))}});
    else {
        pressed.find(DOWN2P)->second.first = sf::Keyboard::S;
        pressed.find(DOWN2P)->second.second->replace(
            0, pressed.find(DOWN2P)->second.second->size(),
            convertInput(sf::Keyboard::S));
    }
    if (pressed.find(LEFT2P) == pressed.end())
        pressed.insert({LEFT2P,
                        {sf::Keyboard::Q, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::Q))}});
    else {
        pressed.find(LEFT2P)->second.first = sf::Keyboard::Q;
        pressed.find(LEFT2P)->second.second->replace(
            0, pressed.find(LEFT2P)->second.second->size(),
            convertInput(sf::Keyboard::Q));
    }
    if (pressed.find(RIGHT2P) == pressed.end())
        pressed.insert({RIGHT2P,
                        {sf::Keyboard::D, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::D))}});
    else {
        pressed.find(RIGHT2P)->second.first = sf::Keyboard::D;
        pressed.find(RIGHT2P)->second.second->replace(
            0, pressed.find(RIGHT2P)->second.second->size(),
            convertInput(sf::Keyboard::D));
    }
    released.insert({UP2R, sf::Keyboard::Z});
    released.insert({DOWN2R, sf::Keyboard::S});
    released.insert({LEFT2R, sf::Keyboard::Q});
    released.insert({RIGHT2R, sf::Keyboard::D});
    if (pressed.find(SHOOT2) == pressed.end())
        pressed.insert(
            {SHOOT2,
             {sf::Keyboard::Space, std::make_shared<std::string>(
                                       convertInput(sf::Keyboard::Space))}});
    else {
        pressed.find(SHOOT2)->second.first = sf::Keyboard::Space;
        pressed.find(SHOOT2)->second.second->replace(
            0, pressed.find(SHOOT2)->second.second->size(),
            convertInput(sf::Keyboard::Space));
    }
    if (pressed.find(SUPERSHOOT2) == pressed.end())
        pressed.insert({SUPERSHOOT2,
                        {sf::Keyboard::N, std::make_shared<std::string>(
                                              convertInput(sf::Keyboard::N))}});
    else {
        pressed.find(SUPERSHOOT2)->second.first = sf::Keyboard::N;
        pressed.find(SUPERSHOOT2)
            ->second.second->replace(
                0, pressed.find(SUPERSHOOT2)->second.second->size(),
                convertInput(sf::Keyboard::N));
    }
}

std::string convertInputF(const sf::Keyboard::Key &key) {
    switch (key) {
    case sf::Keyboard::F1:
        return "F1";
    case sf::Keyboard::F2:
        return "F2";
    case sf::Keyboard::F3:
        return "F3";
    case sf::Keyboard::F4:
        return "F4";
    case sf::Keyboard::F5:
        return "F5";
    case sf::Keyboard::F6:
        return "F6";
    case sf::Keyboard::F7:
        return "F7";
    case sf::Keyboard::F8:
        return "F8";
    case sf::Keyboard::F9:
        return "F9";
    case sf::Keyboard::F10:
        return "F10";
    case sf::Keyboard::F11:
        return "F11";
    case sf::Keyboard::F12:
        return "F12";
    case sf::Keyboard::F13:
        return "F13";
    case sf::Keyboard::F14:
        return "F14";
    case sf::Keyboard::F15:
        return "F15";
    default:
        return "Unknow";
    }
}

std::string convertInputSpecial(const sf::Keyboard::Key &key) {
    switch (key) {
    case sf::Keyboard::Escape:
        return "Escape";
    case sf::Keyboard::LControl:
        return "LControl";
    case sf::Keyboard::LShift:
        return "LShift";
    case sf::Keyboard::LAlt:
        return "LAlt";
    case sf::Keyboard::LSystem:
        return "LSystem";
    case sf::Keyboard::RControl:
        return "RControl";
    case sf::Keyboard::RShift:
        return "RShift";
    case sf::Keyboard::RAlt:
        return "RAlt";
    case sf::Keyboard::RSystem:
        return "RSystem";
    case sf::Keyboard::Comma:
        return ",";
    case sf::Keyboard::SemiColon:
        return ";";
    case sf::Keyboard::Slash:
        return ":";
    case sf::Keyboard::Equal:
        return "=";
    case sf::Keyboard::Space:
        return "Space";
    case sf::Keyboard::Enter:
        return "Enter";
    case sf::Keyboard::BackSpace:
        return "BackSpace";
    case sf::Keyboard::Tab:
        return "Tab";
    case sf::Keyboard::Add:
        return "+";
    case sf::Keyboard::Subtract:
        return "-";
    case sf::Keyboard::Multiply:
        return "*";
    case sf::Keyboard::Divide:
        return "/";
    case sf::Keyboard::Left:
        return "Left";
    case sf::Keyboard::Right:
        return "Right";
    case sf::Keyboard::Up:
        return "Up";
    case sf::Keyboard::Down:
        return "Down";
    default:
        return convertInputF(key);
    }
}

std::string convertInputNumber(const sf::Keyboard::Key &key) {
    switch (key) {
    case sf::Keyboard::Num0:
        return "à";
    case sf::Keyboard::Num1:
        return "&";
    case sf::Keyboard::Num2:
        return "é";
    case sf::Keyboard::Num3:
        return "\"";
    case sf::Keyboard::Num4:
        return "'";
    case sf::Keyboard::Num5:
        return "(";
    case sf::Keyboard::Num6:
        return "-";
    case sf::Keyboard::Num7:
        return "è";
    case sf::Keyboard::Num8:
        return "_";
    case sf::Keyboard::Num9:
        return "ç";
    case sf::Keyboard::Numpad0:
        return "0";
    case sf::Keyboard::Numpad1:
        return "1";
    case sf::Keyboard::Numpad2:
        return "2";
    case sf::Keyboard::Numpad3:
        return "3";
    case sf::Keyboard::Numpad4:
        return "4";
    case sf::Keyboard::Numpad5:
        return "5";
    case sf::Keyboard::Numpad6:
        return "6";
    case sf::Keyboard::Numpad7:
        return "7";
    case sf::Keyboard::Numpad8:
        return "8";
    case sf::Keyboard::Numpad9:
        return "9";
    default:
        return convertInputSpecial(key);
    }
}

std::string convertInput(const sf::Keyboard::Key &key) {
    switch (key) {
    case sf::Keyboard::A:
        return "A";
    case sf::Keyboard::B:
        return "B";
    case sf::Keyboard::C:
        return "C";
    case sf::Keyboard::D:
        return "D";
    case sf::Keyboard::E:
        return "E";
    case sf::Keyboard::F:
        return "F";
    case sf::Keyboard::G:
        return "G";
    case sf::Keyboard::H:
        return "H";
    case sf::Keyboard::I:
        return "I";
    case sf::Keyboard::J:
        return "J";
    case sf::Keyboard::K:
        return "K";
    case sf::Keyboard::L:
        return "L";
    case sf::Keyboard::M:
        return "M";
    case sf::Keyboard::N:
        return "N";
    case sf::Keyboard::O:
        return "O";
    case sf::Keyboard::P:
        return "P";
    case sf::Keyboard::Q:
        return "Q";
    case sf::Keyboard::R:
        return "R";
    case sf::Keyboard::S:
        return "S";
    case sf::Keyboard::T:
        return "T";
    case sf::Keyboard::U:
        return "U";
    case sf::Keyboard::V:
        return "V";
    case sf::Keyboard::W:
        return "W";
    case sf::Keyboard::X:
        return "X";
    case sf::Keyboard::Y:
        return "Y";
    case sf::Keyboard::Z:
        return "Z";
    default:
        return convertInputNumber(key);
    }
}

std::string getInput(std::map<UserInput, sf::Keyboard::Key> &input,
                     UserInput search) {
    for (const auto [key, value] : input) {
        if (key == search)
            return convertInput(value);
    }
    return "Unknow";
}

} // namespace rtype::client
