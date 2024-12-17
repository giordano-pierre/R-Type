/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** ReceiveEvent.hpp
*/

#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "NetworkActions.hpp"

struct ReceiveEvent
{
    // ReceiveEvent(NetworkActions action, const nlohmann::json &payload, const std::string &sender_uuid=""):
    //     action(action), payload(payload), sender_uuid(sender_uuid) {};

    const NetworkActions action;
    const nlohmann::json payload;
    const std::string sender_uuid = "";
};
