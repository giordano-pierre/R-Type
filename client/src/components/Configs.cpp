/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Configs
*/

#include "components/Configs.hpp"

namespace rtype::client {

Configs::Configs(TupleUInt size, TupleUInt serverSize)
    : _size(size), _serverSize(serverSize) {
    initGeneralInput(_inputConfig.first);
    initPlay1Input(_inputConfig);
    initPlay2Input(_inputConfig);
}

} // namespace rtype::client
