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
  CPLAYER,
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
};

float computeDist(TupleFloat a, TupleFloat b);
std::string convertInput(const sf::Keyboard::Key &key);
std::string getInput(std::map<UserInput, sf::Keyboard::Key> &input, UserInput search);
} // namespace Rtype::Client
