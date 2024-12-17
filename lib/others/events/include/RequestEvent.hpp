/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** RequestEvent.hpp
*/

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "NetworkActions.hpp"

struct RequestEvent
{
    // RequestEvent(NetworkActions action, const nlohmann::json &payload, const std::string &receiver_uuid=""):
    //     action(action), payload(payload), receiver_uuid(receiver_uuid) {};

    const NetworkActions action;
    const nlohmann::json payload;
    const std::string receiver_uuid = "";
};
