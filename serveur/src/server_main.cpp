/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** server_main
*/

#include <csignal>
#include <cstdlib>
#include <iostream>
// #include "CollisionSystem.hpp"
// #include "GameLogicSystem.hpp"
// #include "HealthSystem.hpp"
// #include "MovementSystem.hpp"
// #include "ServerHandlerSystem.hpp"
#include "Components.hpp"
#include "Events.hpp"
#include "systems/child/EnemiesSystem.hpp"
#include "systems/child/Singleton.hpp"
#include "systems/parent/CheckWinSys.hpp"
#include "systems/parent/LifeSys.hpp"
#include "systems/parent/MainMessageHandlerSys.hpp"
#include "systems/parent/ResendEventSys.hpp"
#include "systems/parent/TriggerChildSys.hpp"
#include "systems/parent/UDPServer.hpp"
#include "systems/parent/UpdateSys.hpp"

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

// void disconnectAll(ECS &ecs)
// {
//     const auto &rooms = ecs.get_components<rtype::server::Room>();

//     for (size_t i = 0; i < rooms.size(); ++i) {
//         const auto &ro = rooms[i];

//         if (ro) {
//             for (const auto &[uuid, _] : ro.value()._clients_uuid) {
//                 ecs.post<
//             }
//         }
//     }
// }

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
    ecs.register_component<rtype::server::EnemyAI>();
    ecs.register_component<rtype::server::Position>();
    ecs.register_component<rtype::server::Velocity>();
    ecs.register_component<rtype::server::HitBox>();
    ecs.register_component<rtype::server::Health>();
    ecs.register_component<rtype::server::Score>();

    ecs.register_event<rtype::server::TicEvent>();
    ecs.register_event<RequestEvent>();
    ecs.register_event<ReceiveEvent>();
    ecs.register_event<rtype::server::CheckEvent>();
    ecs.register_event<rtype::server::UpdateEvent>();
}

void loadMainSystems(ECS &ecs) {
    auto handler = rtype::server::MainMessageHandlerSys();
    ecs.subscribe<ReceiveEvent, rtype::server::Room, rtype::server::Tag,
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

    auto enemiesSys = Singleton<rtype::server::systems::EnemiesSys>();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
                  rtype::server::Tag, rtype::server::EnemyAI,
                  rtype::server::Velocity>(enemiesSys.getInstance());
}

int main(int ac, char *argv[]) {
    // try {
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

        createEnemyWithAI(ecs, { 1900, 300, -5, 0, 0.1f, 0.18f, 100, 80 },
            rtype::server::EnemyAI::BehaviorType::SINUSOIDAL);

        loadMainSystems(ecs);
        serverLoop(ecs);

        ecs.post<RequestEvent>({DISCONNECT, {}});
        if (!ecs.empty()) {
            auto evt = ecs.front();
            evt();
            ecs.pop_front();
        }
        std::cout << "===============================" << std::endl
                  << std::endl;
        std::cout << "... Serveur arrêté avec succès. Bien joué!" << std::endl;
        std::cout << "N'hésite pas a rejoindre Arts&Crafts ;)" << std::endl;
    // } catch (const std::exception &e) {
    //     std::cerr << "Aie aie aie... \nServer error: " << e.what() << std::endl;
    //     return 1;
    // }
    return 0;
}

// int main(int ac, char *argv[]) {
//     try {
//         if (ac != 1 && ac != 2)
//             return 84;

//         if (ac == 3 && !is_number(argv[1]))
//             return 84;

//         std::signal(SIGINT, signalHandler);
//         std::signal(SIGTERM, signalHandler);

//         int port = (ac == 2) ? std::atoi(argv[1]) : 4242;

//         ECS ecs;

//         ecs.register_component<rtype::server::Position>();
//         ecs.register_component<rtype::server::Velocity>();
//         ecs.register_component<rtype::server::HitBox>();
//         ecs.register_component<rtype::server::Tag>();
//         ecs.register_component<rtype::server::Score>();
//         ecs.register_component<rtype::server::Basics>();
//         ecs.register_component<rtype::server::Health>();
//         ecs.register_component<rtype::server::PlayerData>();

//         ecs.register_event<rtype::server::TicEvent>();
//         ecs.register_event<RequestEvent>();
//         ecs.register_event<ReceiveEvent>();

//         UDPServer server(ecs, port);
//         ecs.subscribe<RequestEvent>(server, true);

//         ServerHandlerSystem server_handler;
//         ecs.subscribe<ReceiveEvent>(server_handler, true);

//         Entity basics = ecs.spawn_entity();

//         std::vector<rtype::server::EnemyInfo> enemies = {
//             {2000, 500, -9, 0, 0.1f, 0.18f, 100, 60},
//             {2500, 1000, -8, 0, 0.1f, 0.18f, 100, 30},
//             {2700, 800, -7, 0, 0.1f, 0.18f, 100, 50},
//             {2250, 100, -10, 0, 0.1f, 0.18f, 100, 40}};
//         ecs.add_component<rtype::server::Basics>(basics, {enemies});

//         std::cout << "Démarrage du serveur R-Type..." << std::endl;
//         subscribe_all_systems(ecs);
//         server_loop(ecs);

//         std::cout << "===============================" << std::endl
//                   << std::endl;
//         std::cout << "... Serveur arrêté avec succès. Bien joué!" <<
//         std::endl; std::cout << "N'hésite pas a rejoindre Arts&Crafts ;)" <<
//         std::endl; return 0;

//     } catch (const std::exception &e) {
//         std::cerr << "Aie aie aie... \nServer error: " << e.what() <<
//         std::endl; return 1;
//     }
//     return 0;
// }

// void subscribe_all_systems(ECS &ecs) {
//     auto movementSys = rtype::server::systems::MovementSys();
//     ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
//                   rtype::server::Velocity>(movementSys);

//     auto collisionSys = rtype::server::systems::CollisionSys();
//     ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
//                   rtype::server::HitBox, rtype::server::Tag,
//                   rtype::server::Health, rtype::server::PlayerData,
//                   rtype::server::Score>(collisionSys);
//     ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
//                   rtype::server::Tag, rtype::server::HitBox>(collisionSys);

//     auto healthSys = rtype::server::systems::HealthSys();
//     ecs.subscribe<rtype::server::TicEvent, rtype::server::Health,
//                   rtype::server::Basics>(healthSys);

//     auto gameLogicSys = rtype::server::systems::GameLogicSys();
//     ecs.subscribe<rtype::server::TicEvent, rtype::server::Basics,
//                   rtype::server::Score, rtype::server::Tag>(gameLogicSys);
// }

//         ecs.register_component<rtype::server::Position>();
//         ecs.register_component<rtype::server::Velocity>();
//         ecs.register_component<rtype::server::HitBox>();
//         ecs.register_component<rtype::server::Tag>();
//         ecs.register_component<rtype::server::Score>();
//         ecs.register_component<rtype::server::Basics>();
//         ecs.register_component<rtype::server::Health>();
//         ecs.register_component<rtype::server::PlayerData>();

//         ecs.register_event<rtype::server::TicEvent>();
//         ecs.register_event<RequestEvent>();
//         ecs.register_event<ReceiveEvent>();
