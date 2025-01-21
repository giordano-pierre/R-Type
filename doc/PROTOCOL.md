# Network Protocol Documentation

This document outlines the communication protocol between the server and clients for the multiplayer R-Type-like game.

---

## Message Types

### 1. **Client to Server Messages**
| Message Type            | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| `NEW_CLIENT`            | Sent by the client to initiate a connection with the server.               |
| `CLIENT_READY`          | Sent by the client when ready to start the game. Includes player details.  |
| `CLIENT_INPUT`          | Sent by the client to notify the server of a player input (e.g., movement).|
| `CLIENT_DISCONNECT`     | Sent by the client to disconnect from the game.                            |

#### **Message Details**

- **NEW_CLIENT**  
  - **Purpose**: Request to connect to the server.
  - **Payload**: None.

- **CLIENT_READY(playerName, nb_players_until_game_starts)**  
  - **Purpose**: Notify the server that the client is ready to play.  
  - **Payload**: 
    - `playerName` (string): Name of the player.
    - `nb_players_until_game_starts` (int): Number of players needed to start the game.

- **CLIENT_INPUT(player_id, typeevent)`  
  - **Purpose**: Send a player's input to the server.  
  - **Payload**: 
    - `player_id` (int): ID of the player.
    - `typeevent` (enum): Type of input (e.g., `up`, `down`, `left`, `right`).

- **CLIENT_DISCONNECT**  
  - **Purpose**: Notify the server that the client is disconnecting.  
  - **Payload**: None.

---

### 2. **Server to Client Messages**
| Message Type            | Description                                                                 |
|-------------------------|-----------------------------------------------------------------------------|
| `SEND_UUID`             | Sent by the server to assign a unique ID to the client.                    |
| `READY_SIGNAL`          | Sent by the server to notify that the game is ready to start.              |
| `CREATE_ENTITY`         | Sent by the server to initialize game entities on the client.              |
| `UPDATE_ENTITY`         | Sent by the server to update entity information during gameplay.           |
| `GAME_OVER`             | Sent by the server to notify the client that the game has ended.           |

#### **Message Details**

- **SEND_UUID(uuid)**  
  - **Purpose**: Assign a unique ID to the client.  
  - **Payload**: 
    - `uuid` (int): Unique identifier for the client.

- **READY_SIGNAL**  
  - **Purpose**: Notify all ready players that the game is starting.  
  - **Payload**: None.

- **CREATE_ENTITY(id, type, position, health, velocity, hitbox, score)**  
  - **Purpose**: Provide information about a new game entity to be displayed on the client.  
  - **Payload**: 
    - `id` (int): Entity ID.
    - `type` (enum): Entity type (e.g., `other_player`, `enemy`).
    - `position` (struct): X and Y coordinates of the entity.
    - `health` (int): Health of the entity.
    - `velocity` (struct): X and Y velocity components.
    - `hitbox` (struct): Size and dimensions of the entity's hitbox.
    - `score` (int): Score associated with the entity (if applicable).

- **UPDATE_ENTITY(id, position, health, name)**  
  - **Purpose**: Update information about existing entities during gameplay.  
  - **Payload**: 
    - `id` (int): Entity ID.
    - `position` (struct): Updated X and Y coordinates.
    - `health` (int): Updated health of the entity.
    - `name` (string): Name associated with the entity (if applicable).

- **GAME_OVER**  
  - **Purpose**: Notify the client that the game has ended.  
  - **Payload**: None.

---

## Communication Flow

1. **Connection Phase**:  
   - Client sends `NEW_CLIENT` to the server.  
   - Server responds with `SEND_UUID` to assign a unique ID.

2. **Game Preparation Phase**:  
   - Client sends `CLIENT_READY` with player details when ready.  
   - Server sends `READY_SIGNAL` to all ready clients when the game is ready to start.

3. **Gameplay Phase**:  
   - Server sends `CREATE_ENTITY` messages to initialize game entities on the client.  
   - Client sends `CLIENT_INPUT` messages to notify the server of player actions.  
   - Server periodically sends `UPDATE_ENTITY` messages to synchronize entity states.

4. **Disconnection/End Phase**:  
   - Client can send `CLIENT_DISCONNECT` to leave the game.  
   - Server can send `GAME_OVER` to notify clients that the game has ended.

---

## Data Structures

### **Position** (struct)
- `x` (float): X coordinate.
- `y` (float): Y coordinate.

### **Velocity** (struct)
- `x` (float): X velocity component.
- `y` (float): Y velocity component.

### **Hitbox** (struct)
- `width` (float): Width of the hitbox.
- `height` (float): Height of the hitbox.

---

## Notes
- All communication occurs over a reliable protocol to ensure message delivery.
- Message payloads should be serialized/deserialized appropriately.
