/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** loadSystems
*/

#include "loadSystems.hpp"
#include "ecsObjects.hpp"

namespace Rtype::Client {

void loadGameSystem(ECS &ecs) {
  auto pauseSys = PauseSys();
  ecs.subscribe<InputEvent, Drawable>(pauseSys);
  ecs.subscribe<InputEvent, Velocity>(pauseSys);

  auto moveSys = MoveSys();
  ecs.subscribe<TicEvent, Position, Velocity>(moveSys);
  ecs.subscribe<InputEvent, Playable, Velocity>(moveSys);

  auto borderSys = BorderSys();
  ecs.subscribe<TicEvent, Window, Tag, Hitbox, Position>(borderSys);

  auto shootSys = ShootSys();
  ecs.subscribe<InputEvent, Window, Playable, Position, Hitbox>(shootSys);
}

void loadMenuSystem(ECS &ecs) {
  auto selSys = SelectSys();
  ecs.subscribe<InputEvent, Position, Drawable, Hitbox, Selectable>(selSys);
  ecs.subscribe<InputEvent, Position, Drawable, Selectable>(selSys);

  auto pressSys = PressButtonSys();
  ecs.subscribe<InputEvent, Position, Hitbox, Selectable, Pressable>(pressSys);
  ecs.subscribe<InputEvent, Selectable, Pressable>(pressSys);

}

} // namespace Rtype::Client
