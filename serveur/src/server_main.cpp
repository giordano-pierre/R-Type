#include "CollisionSystem.hpp"
#include "GameLogicSystem.hpp"
#include "HealthSystem.hpp"
#include "MovementSystem.hpp"
#include "ServerHandlerSystem.hpp"
#include "UDPServer.hpp"
#include <csignal>
#include <cstdlib>
#include <iostream>

bool running = true;

void signalHandler(int signum) {
    std::cout << "\nSignal d'arrêt reçu :'(. Arrêt du serveur... \n\n"
              << std::endl;
    running = false;
}

void subscribe_all_systems(ECS &ecs) {
    auto movementSys = rtype::server::systems::MovementSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
                  rtype::server::Velocity>(movementSys);

    auto collisionSys = rtype::server::systems::CollisionSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
                  rtype::server::HitBox, rtype::server::Tag,
                  rtype::server::Health, rtype::server::PlayerData,
                  rtype::server::Score>(collisionSys);
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Position,
                  rtype::server::Tag, rtype::server::HitBox>(collisionSys);

    auto healthSys = rtype::server::systems::HealthSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Health,
                  rtype::server::Basics>(healthSys);

    auto gameLogicSys = rtype::server::systems::GameLogicSys();
    ecs.subscribe<rtype::server::TicEvent, rtype::server::Basics,
                  rtype::server::Score>(gameLogicSys);
}

void server_loop(ECS &ecs) {
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
            ecs.post<rtype::server::TicEvent>(
                {std::chrono::steady_clock::now()});
            dtimeU = std::chrono::duration<double>::zero();
            updateEntity(ecs);
            trigger = true;
        }
        if (trigger) {
            while (!ecs.empty()) {
                auto evt = ecs.front();
                evt();
                ecs.pop_front();
            }
        }
    }
}

void waiting_loop(ECS &ecs) {
    rtype::server::Basics basic =
        ecs.get_components<rtype::server::Basics>()[0].value();

    while (basic.minPlayer != basic.nbPlayer) {

        basic = ecs.get_components<rtype::server::Basics>()[0].value();
    }
}

int main() {
    try {
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);

        ECS ecs;

        ecs.register_component<rtype::server::Position>();
        ecs.register_component<rtype::server::Velocity>();
        ecs.register_component<rtype::server::HitBox>();
        ecs.register_component<rtype::server::Tag>();
        ecs.register_component<rtype::server::Score>();
        ecs.register_component<rtype::server::Basics>();
        ecs.register_component<rtype::server::Health>();
        ecs.register_component<rtype::server::PlayerData>();

        ecs.register_event<rtype::server::TicEvent>();
        ecs.register_event<RequestEvent>();
        ecs.register_event<ReceiveEvent>();

        UDPServer server(ecs, 4242);
        ecs.subscribe<RequestEvent>(server, true);

        ServerHandlerSystem server_handler;
        ecs.subscribe<ReceiveEvent>(server_handler, true);

        Entity basics = ecs.spawn_entity();

        std::vector<rtype::server::EnemyInfo> enemies = {
            {2000, 500, 9, 0, 0.1f, 0.18f, 100, 60},
            {2500, 1000, 8, 0, 0.1f, 0.18f, 100, 30},
            {2700, 800, 7, 0, 0.1f, 0.18f, 100, 50},
            {2250, 100, 10, 0, 0.1f, 0.18f, 100, 40}};
        ecs.add_component<rtype::server::Basics>(basics, {enemies});

        std::cout << "Attention!!! \nDémarrage du serveur R-Type...\n"
                  << std::endl;
        subscribe_all_systems(ecs);
        server_loop(ecs);

        std::cout << "===============================\n" << std::endl;
        std::cout << "\n... Serveur arrêté avec succès. Bien joué "
                     "!\n\n\n\n\nN'hésite pas a rejoindre Arts&Crafts ;)"
                  << std::endl;
        return 0;

    } catch (const std::exception &e) {
        std::cerr << "Aie aie aie... \nServer error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
