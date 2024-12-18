/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tools
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace Rtype::Client {
struct TupleInt {
  int x;
  int y;
};

struct TupleUInt {
  unsigned int x;
  unsigned int y;
};

struct TupleFloat {
  float x;
  float y;
};

enum ObjectType {
  WINDOW,
  PLAYER,
  BACKGROUND,
  SHOT,
  MENU,
  CONFIG,
  CGENERAL,
  CPLAYER1,
};

enum UserInput {
  NOTHING = 0,
  ENTER,
  PAUSE,
  QUIT,
  RETURN,
  UP1P,
  UP1R,
  DOWN1P,
  DOWN1R,
  LEFT1P,
  LEFT1R,
  RIGHT1P,
  RIGHT1R,
  SHOOT1,
  SUPERSHOOT1,
  UP2P,
  UP2R,
  DOWN2P,
  DOWN2R,
  LEFT2P,
  LEFT2R,
  RIGHT2P,
  RIGHT2R,
  SHOOT2,
  SUPERSHOOT2,
};

float computeDist(TupleFloat a, TupleFloat b);
std::string convertInput(const sf::Keyboard::Key &key);
std::string getInput(std::map<UserInput, sf::Keyboard::Key> &input,
                     UserInput search);
void initGeneralInput(std::map<UserInput, sf::Keyboard::Key> &inputConfig);
void initPlay1Input(
    std::pair<std::map<UserInput, sf::Keyboard::Key>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig);
void initPlay2Input(
    std::pair<std::map<UserInput, sf::Keyboard::Key>,
              std::map<UserInput, sf::Keyboard::Key>> &inputConfig);
} // namespace Rtype::Client
