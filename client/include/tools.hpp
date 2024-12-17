/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** tools
*/

#pragma once

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
  DOWN1P,
  LEFT1P,
  RIGHT1P,
  UP1R,
  DOWN1R,
  LEFT1R,
  RIGHT1R,
  SHOOT1,
  SUPERSHOOT1,
};

float computeDist(TupleFloat a, TupleFloat b);
} // namespace Rtype::Client
