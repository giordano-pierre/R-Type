/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ecsObjects
*/

#pragma once

#include "components/Drawable.hpp"
#include "components/Hitbox.hpp"
#include "components/Playable.hpp"
#include "components/Position.hpp"
#include "components/Pressable.hpp"
#include "components/Selectable.hpp"
#include "components/Tag.hpp"
#include "components/Text.hpp"
#include "components/Velocity.hpp"
#include "components/Window.hpp"

#include "events/ChangeKey.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"

#include "systems/BorderSys.hpp"
#include "systems/CheatSys.hpp"
#include "systems/FrameSys.hpp"
#include "systems/MoveSys.hpp"
#include "systems/PauseSys.hpp"
#include "systems/PressButtonSys.hpp"
#include "systems/SelectSys.hpp"
#include "systems/ShootSys.hpp"
#include "systems/WindowSys.hpp"
