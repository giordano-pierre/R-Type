/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** server_main
*/

#include "Components.hpp"
#include "Events.hpp"
#include "systems/child/EnemiesSystem.hpp"
#include "systems/parent/CheckWinSys.hpp"
#include "systems/parent/LifeSys.hpp"
#include "systems/parent/MainMessageHandlerSys.hpp"
#include "systems/parent/ResendEventSys.hpp"
#include "systems/parent/TriggerChildSys.hpp"
#include "systems/parent/UDPServer.hpp"
#include "systems/parent/UpdateSys.hpp"
#include <csignal>
#include <cstdlib>
#include <iostream>

bool running = true;

void signalHandler(int signum) {
    std::cout << std::endl
              << "Signal d'arrêt reçu :'(. Arrêt du serveur..." << std::endl;
    running = false;
}

void serverLoop(ECS &ecs) {
    const auto FPS = 60;
    const timer::duration<double, std::ratio<1, FPS>> frameRate(1);
    timer::time_point<timer::steady_clock> frameStart;
    timer::duration<double> dtimeF = timer::duration<double>::zero();

    const auto Update = 25;
    const timer::duration<double, std::ratio<1, Update>> updateRate(1);
    timer::time_point<timer::steady_clock> updateStart;
    timer::duration<double> dtimeU = timer::duration<double>::zero();

    timer::time_point<timer::steady_clock> newTime;

    while (running) {
        bool trigger = false;
        newTime = timer::steady_clock::now();
        dtimeF += newTime - frameStart;
        frameStart = newTime;
        dtimeU += newTime - updateStart;
        updateStart = newTime;

        if (dtimeF >= frameRate) {
            ecs.post<rtype::server::TicEvent>(
                {std::chrono::steady_clock::now()});
            dtimeF = std::chrono::duration<double>::zero();
            trigger = true;
        }
        if (dtimeU >= updateRate) {
            ecs.post<rtype::server::UpdateEvent>(
                {std::chrono::steady_clock::now()});
            dtimeU = std::chrono::duration<double>::zero();
            trigger = true;
        }
        if (trigger) {
            while (!ecs.empty()) {
                auto &evt = ecs.front();
                evt();
                ecs.pop_front();
            }
        }
    }
}

bool is_number(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

void initMainECS(ECS &ecs) {
    ecs.register_component<rtype::server::Tag>();
    ecs.register_component<rtype::server::Room>();
    ecs.register_component<rtype::server::Stage>();
    ecs.register_component<rtype::server::Child>();
    ecs.register_component<rtype::server::Utils>();
    ecs.register_component<rtype::server::Position>();

    ecs.register_event<rtype::server::TicEvent>();
    ecs.register_event<RequestEvent>();
    ecs.register_event<ReceiveEvent>();
    ecs.register_event<rtype::server::CheckEvent>();
    ecs.register_event<rtype::server::UpdateEvent>();

    Entity base = ecs.spawn_entity();
    ecs.add_component<rtype::server::Utils>(base, {});
}

void loadMainSystems(ECS &ecs) {
    auto handler = rtype::server::MainMessageHandlerSys();
    ecs.subscribe<ReceiveEvent, rtype::server::Utils, rtype::server::Room,
                  rtype::server::Tag, rtype::server::Stage,
                  rtype::server::Child>(handler, true);
    auto resend = rtype::server::ResendEventSys();
    ecs.subscribe<rtype::server::CheckEvent, rtype::server::Room,
                  rtype::server::Tag>(resend, true);
    auto check = rtype::server::CheckWinSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Tag,
                  rtype::server::Room, rtype::server::Stage,
                  rtype::server::Child>(check, true);
    auto life = rtype::server::LifeSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Child,
                  rtype::server::Room>(life, true);
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Room,
                  rtype::server::Stage, rtype::server::Child>(life, true);
    auto trigger = rtype::server::TriggerChildSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Child>(trigger, true);
    auto update = rtype::server::UpdateSys();
    ecs.subscribe<rtype::server::UpdateEvent, rtype::server::Room,
                  rtype::server::Child>(update);
}

int main(int ac, char *argv[]) {
    try {
    if (ac != 1 && ac != 2)
        return 84;

    if (ac == 3 && !is_number(argv[1]))
        return 84;

    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    int port = (ac == 2) ? std::atoi(argv[1]) : 4242;
    std::cout << "Démarrage du serveur R-Type..." << std::endl;

    ECS ecs;
    initMainECS(ecs);

    rtype::server::UDPServer server(ecs, port);
    ecs.subscribe<RequestEvent>(server, true);

    loadMainSystems(ecs);
    serverLoop(ecs);

    ecs.post<RequestEvent>({DISCONNECT, {}});
    if (!ecs.empty()) {
        auto evt = ecs.front();
        evt();
        ecs.pop_front();
    }
    std::cout << "===============================" << std::endl << std::endl;
    std::cout << "... Serveur arrêté avec succès. Bien joué!" << std::endl;
    std::cout << "N'hésite pas a rejoindre Arts&Crafts ;)" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Aie aie aie... \nServer error: " << e.what() <<
        std::endl; return 1;
    }
    return 0;
}
