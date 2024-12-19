/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** NetworkActions.hpp
*/

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

enum NetworkActions {
    CONNECT = 1,
    ENVOI_SERV,
    ENVOI_CLIENT,
    NEW_CLIENT,
    SEND_UUID,
    CLIENT_READY,
    SERVER_READY,
    CLIENT_CREATE,
    CREATE_ENTITY,
    UPDATE_ENTITY,
    CLIENT_INPUT,
    CLIENT_DISCONNECT,
};

inline std::string fetch_new_uuid() {
    boost::uuids::random_generator uuid_generator_;
    return boost::uuids::to_string(uuid_generator_());
}