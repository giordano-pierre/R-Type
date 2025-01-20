/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ecsObjects
*/

#pragma once

#include "components/Configs.hpp"
#include "components/Drawable.hpp"
#include "components/Health.hpp"
#include "components/Hitbox.hpp"
#include "components/LastUpdate.hpp"
#include "components/Playable.hpp"
#include "components/PlayerData.hpp"
#include "components/PlayerInfo.hpp"
#include "components/Position.hpp"
#include "components/Pressable.hpp"
#include "components/Room.hpp"
#include "components/SFMLObjects.hpp"
#include "components/Scene.hpp"
#include "components/Score.hpp"
#include "components/Selectable.hpp"
#include "components/Tag.hpp"
#include "components/Text.hpp"
#include "components/Velocity.hpp"

#include "events/AnimeEvent.hpp"
#include "events/ChangeKey.hpp"
#include "events/CreateEvent.hpp"
#include "events/DeleteEvent.hpp"
#include "events/FrameEvent.hpp"
#include "events/InputEvent.hpp"
#include "events/TicEvent.hpp"

#include "systems/AnimeSys.hpp"
#include "systems/BorderSys.hpp"
#include "systems/CheatSys.hpp"
#include "systems/LifeSys.hpp"
#include "systems/MoveSys.hpp"
#include "systems/PauseSys.hpp"
#include "systems/PressButtonSys.hpp"
#include "systems/SelectSys.hpp"
#include "systems/ShootSys.hpp"
#include "systems/WindowSys.hpp"
#include "systems/KillEntity.hpp"
