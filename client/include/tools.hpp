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
        BUTTON,
    };

    enum UserInput {
        NOTHING = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER,
        PAUSE,
        SHOOT,
        SUPERSHOOT,
        RETURN,
        QUIT,
    };

    float computeDist(TupleFloat a, TupleFloat b);
}
