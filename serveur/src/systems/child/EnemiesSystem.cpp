/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemiesSystem.cpp
*/

#include "systems/child/EnemiesSystem.hpp"

namespace rtype::server {
    EnemiesSys::EnemiesSys() { initLua(); }

    void EnemiesSys::initLua() {
        lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
        registerComponents();
        loadBehaviors();
    }
    void EnemiesSys::registerComponents() {
        lua.new_enum<EnemyAI::BehaviorType>(
            "BehaviorType", { {"SINUSOIDAL", EnemyAI::BehaviorType::SINUSOIDAL},
                             {"CIRCULAR", EnemyAI::BehaviorType::CIRCULAR},
                             {"CHASE", EnemyAI::BehaviorType::CHASE},
                             {"V_FORMATION", EnemyAI::BehaviorType::V_FORMATION},
                             {"BOSS", EnemyAI::BehaviorType::BOSS} });

        lua.new_usertype<EnemyAI>("EnemyAI", "behaviorType", &EnemyAI::behaviorType,
            "amplitude", &EnemyAI::amplitude, "frequency",
            &EnemyAI::frequency, "radius", &EnemyAI::radius,
            "speed", &EnemyAI::speed, "spacing",
            &EnemyAI::spacing, "index", &EnemyAI::index);

        lua.new_usertype<Position>("Position", "x", &Position::x, "y",
            &Position::y);

        lua.new_usertype<Velocity>("Velocity", "x", &Velocity::x, "y",
            &Velocity::y);
    }

    void EnemiesSys::loadBehaviors() {
        try {
            lua.script_file(scriptsPath);
        }
        catch (const sol::error& e) {
            std::cerr << "Erreur lors du chargement des comportements: " << e.what()
                << std::endl;
        }
    }

    void EnemiesSys::operator()(ECS& ecs, const rtype::server::TicEvent& tic,
        SparseArray<Position>& positions,
        const SparseArray<Tag>& tags,
        SparseArray<EnemyAI>& ais,
        SparseArray<Velocity>& velocities) {
        const auto& players =
            ecs.get_components<PlayerData>();

        rtype::server::Position posPlayer(0, 0);

        for (size_t i = 0; i < players.size(); ++i){
            if(players[i]) {
                posPlayer = *positions[i];
                break;
            }
        }
        for (size_t i = 0; i < positions.size(); ++i) {
            if (!positions[i] || !tags[i] || !ais[i] || !velocities[i])
                continue;
            if ((*tags[i])._type != EntityType::ENEMY1)
                continue;
            auto& pos = *positions[i];
            auto& ai = *ais[i];
            auto& vel = *velocities[i];
            static timer::time_point<timer::steady_clock> lastTic = tic.time_stamp;
            float delta =
                std::chrono::duration<float>(tic.time_stamp - lastTic).count();
            lastTic = tic.time_stamp;
            updateBehavior(pos, vel, ai, delta, posPlayer);
        }
    }

    void EnemiesSys::updateBehavior(Position& pos, Velocity& vel, EnemyAI& ai,
        float dt, rtype::server::Position &posPlayer) {
        switch (ai.behaviorType) {
        case EnemyAI::BehaviorType::SINUSOIDAL: {
            sol::function update = lua["SineMovement"]["update"];
            if (update.valid()) {
                sol::protected_function_result result =
                    update(lua["SineMovement"], pos, vel, ai, dt);
                if (!result.valid()) {
                    sol::error err = result;
                    std::cerr << "Lua error: " << err.what() << std::endl;
                }
            }
            break;
        }
        case EnemyAI::BehaviorType::CIRCULAR: {
            sol::function update = lua["CircleMovement"]["update"];
            if (update.valid()) {
                update(lua["CircleMovement"], pos, vel, ai, dt);
            }
            break;
        }
        case EnemyAI::BehaviorType::CHASE: {
            sol::function update = lua["PlayerChase"]["update"];
            if (update.valid()) {
            update(lua["PlayerChase"], pos, vel, ai, posPlayer, dt);
            }
            break;
        }
        case EnemyAI::BehaviorType::V_FORMATION: {
            sol::function update = lua["VFormation"]["update"];
            if (update.valid()) {
                update(pos, vel, ai, dt);
            }
            break;
        }
        case EnemyAI::BehaviorType::BOSS: {
            sol::function update = lua["BossBehavior"]["update"];
            if (update.valid()) {
                update(lua["BossBehavior"],pos, vel, ai, dt);
            }
            break;
        }
        case EnemyAI::BehaviorType::UPDOWN: {
            sol::function update = lua["UpDown"]["update"];
            if (update.valid()) {
                update(lua["UpDown"], pos, vel, ai, dt);
            }
            break;
        }
        }
    }

} // namespace rtype::server

RequestEvent createEnemyWithAI(ECS& ecs, rtype::server::EnemyInfo enemyInfo,
    rtype::server::EnemyAI::BehaviorType behavior) {
    Entity entity = ecs.spawn_entity();
    std::string uuid = fetch_new_uuid();

    ecs.add_component<rtype::server::Position>(
        entity, { enemyInfo.x_pos, enemyInfo.y_pos });

    ecs.add_component<rtype::server::Velocity>(
        entity, { enemyInfo.x_velocity, enemyInfo.y_velocity, true });

    ecs.add_component<rtype::server::HitBox>(
        entity, { enemyInfo.x_hitbox, enemyInfo.y_hitbox });

    ecs.add_component<rtype::server::Health>(entity, {});
    ecs.add_component<rtype::server::Score>(entity, { enemyInfo.score });
    ecs.add_component<rtype::server::Tag>(entity, { uuid, EntityType::ENEMY1 });

    switch (behavior) {
    case rtype::server::EnemyAI::BehaviorType::SINUSOIDAL:
        ecs.add_component<rtype::server::EnemyAI>(
            entity, rtype::server::EnemyAI{ .behaviorType = behavior,
                                           .amplitude = 5.0f,
                                           .frequency = 2.0f });
        break;

    case rtype::server::EnemyAI::BehaviorType::CIRCULAR:
        ecs.add_component<rtype::server::EnemyAI>(
            entity, rtype::server::EnemyAI{ .behaviorType = behavior,
                                           .radius = 50.0f,
                                           .speed = 3.0f });
        break;

    case rtype::server::EnemyAI::BehaviorType::CHASE:
        ecs.add_component<rtype::server::EnemyAI>(
            entity,
            rtype::server::EnemyAI{ .behaviorType = behavior, .speed = 3.0f });
        break;

    case rtype::server::EnemyAI::BehaviorType::V_FORMATION:
        ecs.add_component<rtype::server::EnemyAI>(
            entity, rtype::server::EnemyAI{ .behaviorType = behavior,
                                           .spacing = 40.0f,
                                           .index = 0 });
        break;

    case rtype::server::EnemyAI::BehaviorType::BOSS:
        ecs.add_component<rtype::server::EnemyAI>(
            entity, rtype::server::EnemyAI{ .behaviorType = behavior,
                                           .amplitude = 100.0f,
                                           .frequency = 1.0f,
                                           .radius = 200.0f,
                                           .speed = 5.0f });
        break;

    case rtype::server::EnemyAI::BehaviorType::UPDOWN:
        ecs.add_component<rtype::server::EnemyAI>(
            entity, rtype::server::EnemyAI{ .behaviorType = behavior,
                                           .speed = 5.0f });
        break;
    }
    return RequestEvent(
        { Protocol::SV_CREATE_ENTITY,
         {{"id", uuid},
          {"type", EntityType::ENEMY1},
          {"pos", {{"x", enemyInfo.x_pos}, {"y", enemyInfo.y_pos}}},
          {"hp", enemyInfo.health},
          {"vel", {{"x", enemyInfo.x_velocity}, {"y", enemyInfo.y_velocity}}},
          {"hit", {{"x", enemyInfo.x_hitbox}, {"y", enemyInfo.y_hitbox}}},
          {"sc", enemyInfo.score}},
         "" });
}

std::vector<RequestEvent> createSineEnemy(ECS& ecs, rtype::server::EnemyInfo enemy) {
    rtype::server::EnemyInfo info{ .x_pos = enemy.x_pos,
                                  .y_pos = enemy.y_pos,
                                  .x_velocity = 0,
                                  .y_velocity = 0,
                                  .x_hitbox = enemy.x_hitbox,
                                  .y_hitbox = enemy.y_hitbox,
                                  .health = 100,
                                  .score = 100 };
    return { createEnemyWithAI(ecs, info,
                             rtype::server::EnemyAI::BehaviorType::SINUSOIDAL) };
}

std::vector<RequestEvent> createVFormation(ECS& ecs, rtype::server::EnemyInfo enemy) {
    std::vector<RequestEvent> response;
    std::vector<rtype::server::Position> pos = {
        {2000, 500},
        {2200, 350},
        {2200, 650},
        {2400, 200},
        {2400, 800},
        {2600, 50},
        {2600, 950},
    };
    for (int i = 0; i < 5; i++) {
        rtype::server::EnemyInfo info{ .x_pos = pos[i].x,
                                      .y_pos = pos[i].y,
                                      .x_velocity = -2,
                                      .y_velocity = 1,
                                      .x_hitbox = enemy.x_hitbox,
                                      .y_hitbox = enemy.y_hitbox,
                                      .health = 100,
                                      .score = 150 };
        response.push_back(createEnemyWithAI(ecs, info,
            rtype::server::EnemyAI::BehaviorType::V_FORMATION));
    }
    return response;
}


std::vector<RequestEvent> createCircle(ECS& ecs, rtype::server::EnemyInfo enemy) {
    rtype::server::EnemyInfo info{ .x_pos = enemy.x_pos,
                                  .y_pos = enemy.y_pos,
                                  .x_velocity = -2,
                                  .y_velocity = 0,
                                  .x_hitbox = enemy.x_hitbox,
                                  .y_hitbox = enemy.y_hitbox,
                                  .health = 100,
                                  .score = 100 };
    return { createEnemyWithAI(ecs, info,
                             rtype::server::EnemyAI::BehaviorType::CIRCULAR) };
}

std::vector<RequestEvent> createChase(ECS& ecs, rtype::server::EnemyInfo enemy) {
    rtype::server::EnemyInfo info{ .x_pos = enemy.x_pos,
                                  .y_pos = enemy.y_pos,
                                  .x_velocity = -2,
                                  .y_velocity = 0,
                                  .x_hitbox = enemy.x_hitbox,
                                  .y_hitbox = enemy.y_hitbox,
                                  .health = 100,
                                  .score = 100 };
    return { createEnemyWithAI(ecs, info,
                             rtype::server::EnemyAI::BehaviorType::CHASE) };
}

std::vector<RequestEvent> createUpDown(ECS& ecs, rtype::server::EnemyInfo enemy) {
    rtype::server::EnemyInfo info{ .x_pos = enemy.x_pos,
                                  .y_pos = enemy.y_pos,
                                  .x_velocity = -3,
                                  .y_velocity = -6,
                                  .x_hitbox = enemy.x_hitbox,
                                  .y_hitbox = enemy.y_hitbox,
                                  .health = 100,
                                  .score = 100 };
    return { createEnemyWithAI(ecs, info,
                             rtype::server::EnemyAI::BehaviorType::UPDOWN) };
}

std::vector<RequestEvent> createBoss(ECS& ecs, rtype::server::EnemyInfo enemy) {
    rtype::server::EnemyInfo info{ .x_pos = enemy.x_pos,
                                  .y_pos = enemy.y_pos,
                                  .x_velocity = -3,
                                  .y_velocity = -6,
                                  .x_hitbox = enemy.x_hitbox,
                                  .y_hitbox = enemy.y_hitbox,
                                  .health = 100,
                                  .score = 100 };
    return { createEnemyWithAI(ecs, info,
                             rtype::server::EnemyAI::BehaviorType::UPDOWN) };
}