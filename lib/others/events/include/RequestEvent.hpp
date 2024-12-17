/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RequestEvent.hpp
*/

#pragma once

#include "NetworkActions.hpp"
#include <nlohmann/json.hpp>
#include <string>

struct RequestEvent {
  // RequestEvent(NetworkActions action, const nlohmann::json &payload, const
  // std::string &receiver_uuid=""):
  //     action(action), payload(payload), receiver_uuid(receiver_uuid) {};

  const NetworkActions action;
  const nlohmann::json payload;
  const std::string receiver_uuid = "";
};
