# Game Engine ECS Documentation

## Overview
This documentation outlines the structure and usage of the **Entity-Component-System (ECS)** implemented for a game engine. The ECS is designed to efficiently manage entities, components, and systems, allowing for modular and scalable game development. Below, we provide a detailed description of the architecture, methods, and practical examples to use this ECS.

---

## ECS Architecture
The ECS is composed of the following key components:

1. **Entities**: Unique identifiers representing objects in the game world.
2. **Components**: Data structures attached to entities that define their properties or state.
3. **Systems**: Logic that operates on entities with specific components.

### Entities
Entities are lightweight objects identified by a unique index. They can have multiple components attached to them.

#### Methods:
- **`spawn_entity()`**: Creates a new entity. Returns an `Entity` object.
- **`entity_from_index(std::size_t idx)`**: Retrieves an entity from its index.
- **`kill_entity(const Entity &entity)`**: Destroys an entity and removes all its components.

### Components
Components store data and are managed using a `SparseArray` container for memory efficiency. Each component type is registered explicitly.

#### Methods:
- **`register_component<Component>()`**: Registers a new component type.
- **`get_components<Component>()`**: Retrieves the array of components of a specific type.
- **`add_component<Entity, Component>()`**: Adds a component to an entity.
- **`remove_component<Entity, Component>()`**: Removes a component from an entity.

### Systems
Systems contain logic applied to entities with specific components. They are subscribed to events and executed when events are posted.

#### Methods:
- **`subscribe<Event, Components...>(System &&system, bool permanent = false)`**: Subscribes a system to an event. By default, systems are not permanent.
- **`clean<Event>()`**: Removes all non-permanent systems subscribed to an event.
- **`post<Event>()`**: Triggers an event, invoking all subscribed systems.

---

## Usage
### Initialization
To set up the ECS for a game:
1. Instantiate the `ECS` class.
2. Register the required component types.
3. Subscribe systems to events.

#### Example
```cpp
#include "ECS.hpp"

// Define components
struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

// Define event
struct UpdateEvent {
    float delta_time;
};

int main() {
    ECS ecs;

    // Register components
    ecs.register_component<Position>();
    ecs.register_component<Velocity>();

    // Spawn entity
    Entity player = ecs.spawn_entity();
    ecs.add_component(player, Position{0.0f, 0.0f});
    ecs.add_component(player, Velocity{1.0f, 0.5f});

    // Subscribe a system to update positions
    ecs.subscribe<UpdateEvent, Position, Velocity>(
        [](ECS &ecs, const UpdateEvent &event, SparseArray<Position> &positions, SparseArray<Velocity> &velocities) {
            for (size_t i = 0; i < positions.size(); ++i) {
                if (positions[i] && velocities[i]) {
                    positions[i]->x += velocities[i]->dx * event.delta_time;
                    positions[i]->y += velocities[i]->dy * event.delta_time;
                }
            }
        }
    );

    // Post an update event
    ecs.post(UpdateEvent{0.016f}); // 16 ms frame

    return 0;
}
```

### Adding Components
Components can be added to entities using `add_component` or `emplace_component`:

```cpp
ecs.add_component(player, Position{100.0f, 200.0f});
ecs.emplace_component<Velocity>(player, 2.0f, 1.5f);
```

### Removing Components
Remove components when they are no longer needed:

```cpp
ecs.remove_component<Position>(player);
```

### Cleaning Systems
Remove non-permanent systems to manage resources efficiently:

```cpp
ecs.clean<UpdateEvent>();
```

---

## Advanced Features
### Permanent Systems
When subscribing a system, set `permanent = true` to ensure it persists across clean operations:

```cpp
ecs.subscribe<UpdateEvent, Position>(
    [](ECS &ecs, const UpdateEvent &event, SparseArray<Position> &positions) {
        // Logic for permanent system
    },
    true // Mark as permanent
);
```

### Custom Events
Define custom events and use them to trigger specific systems. For example:

```cpp
struct CollisionEvent {
    Entity entity1;
    Entity entity2;
};

ecs.subscribe<CollisionEvent, Position>(
    [](ECS &ecs, const CollisionEvent &event, SparseArray<Position> &positions) {
        // Handle collision
    }
);
```

Post the event as needed:

```cpp
ecs.post(CollisionEvent{entity1, entity2});
```

---

## Best Practices
1. **Modular Design**: Keep components simple and focused. Delegate logic to systems.
2. **Event-Driven Architecture**: Use events to decouple systems and improve scalability.
3. **Efficient Resource Management**: Regularly clean up non-permanent systems to optimize performance.

---

## Conclusion
The ECS framework provides a robust and flexible foundation for game development. By separating data (components), logic (systems), and identity (entities), it ensures scalability, maintainability, and performance. Follow the examples and best practices above to maximize the potential of this ECS in your projects.

