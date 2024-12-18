/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tools
*/

#include <cmath>

#include "tools.hpp"

namespace Rtype::Client {

float computeDist(TupleFloat a, TupleFloat b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void initGeneralInput(std::map<UserInput, sf::Keyboard::Key> &inputConfig) {
    inputConfig.insert({ENTER, sf::Keyboard::Enter});
    inputConfig.insert({PAUSE, sf::Keyboard::P});
    inputConfig.insert({RETURN, sf::Keyboard::Q});
    inputConfig.insert({QUIT, sf::Keyboard::Escape});
}

void initPlay1Input(
    std::pair<std::map<UserInput, sf::Keyboard::Key>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig) {
    auto &pressed = inputConfig.first;
    auto &released = inputConfig.second;
    pressed.insert({UP1P, sf::Keyboard::Up});
    pressed.insert({DOWN1P, sf::Keyboard::Down});
    pressed.insert({LEFT1P, sf::Keyboard::Left});
    pressed.insert({RIGHT1P, sf::Keyboard::Right});
    released.insert({UP1R, sf::Keyboard::Up});
    released.insert({DOWN1R, sf::Keyboard::Down});
    released.insert({LEFT1R, sf::Keyboard::Left});
    released.insert({RIGHT1R, sf::Keyboard::Right});
    pressed.insert({SHOOT1, sf::Keyboard::Enter});
    pressed.insert({SUPERSHOOT1, sf::Keyboard::M});
}

void initPlay2Input(
    std::pair<std::map<UserInput, sf::Keyboard::Key>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig) {
    auto &pressed = inputConfig.first;
    auto &released = inputConfig.second;
    pressed.insert({UP2P, sf::Keyboard::Z});
    pressed.insert({DOWN2P, sf::Keyboard::S});
    pressed.insert({LEFT2P, sf::Keyboard::Q});
    pressed.insert({RIGHT2P, sf::Keyboard::D});
    released.insert({UP2R, sf::Keyboard::Z});
    released.insert({DOWN2R, sf::Keyboard::S});
    released.insert({LEFT2R, sf::Keyboard::Q});
    released.insert({RIGHT2R, sf::Keyboard::D});
    pressed.insert({SHOOT2, sf::Keyboard::Space});
    pressed.insert({SUPERSHOOT2, sf::Keyboard::N});
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

} // namespace Rtype::Client
