--[[
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemiesComponant.lua
--]]

SineMovement = {
    time = 0
}
-- add gestion d'eereur division par 0
function SineMovement:update(position, velocity, ai, dt)
    self.time = (self.time or 0) + dt
    velocity.y = math.floor(ai.amplitude * math.sin(self.time))
end

CircleMovement = {
    angle = 0,
    centerX = 0,
    centerY = 0
}
function CircleMovement:update(position, velocity, ai, dt)
    if self.centerX == 0 and self.centerY == 0 then
        self.centerX = position.x
        self.centerY = position.y
    end

    self.angle = self.angle + ai.speed * dt
    position.x = math.floor(self.centerX + ai.radius * math.cos(self.angle))
    position.y = math.floor(self.centerY + ai.radius * math.sin(self.angle))
end

PlayerChase = {}

function PlayerChase:update(position, velocity, ai, playerPos, dt)
    if playerPos then
        local dx = playerPos.x - position.x
        local dy = playerPos.y - position.y
        local distance = math.sqrt(dx * dx + dy * dy)

        if distance > 0 then
            position.x = math.floor(position.x + (dx / distance) * ai.speed * dt)
            position.y = math.floor(position.y + (dy / distance) * ai.speed * dt)
        end
    end
end

VFormation = {}

function VFormation:update(position, velocity, ai, leaderPos, dt)
    if leaderPos then
        local angle = math.pi / 4
        local xOffset = math.cos(angle) * ai.spacing * ai.index
        local yOffset = math.sin(angle) * ai.spacing * ai.index

        if ai.index % 2 == 0 then
            yOffset = -yOffset
        end

        position.x = math.floor(leaderPos.x - xOffset)
        position.y = math.floor(leaderPos.y + yOffset)
    end
end

BossBehavior = {
    currentPhase = 1,
    phaseTimer = 0,
    phaseDuration = 30,
    phases = {
        function(self, position, velocity, ai, dt)
            SineMovement:update(position, velocity, ai, dt)
        end,

        function(self, position, velocity, ai, playerPos, dt)
            PlayerChase:update(position, velocity, ai, playerPos, dt)
        end,

        function(self, position, velocity, ai, dt)
            CircleMovement:update(position, velocity, ai, dt)
        end
    }
}

function BossBehavior:update(position, velocity, ai, playerPos, dt)
    self.phaseTimer = self.phaseTimer + dt

    if self.phaseTimer >= self.phaseDuration then
        self.currentPhase = (self.currentPhase % #self.phases) + 1
        self.phaseTimer = 0
    end

    local phase = self.phases[self.currentPhase]
    if phase then
        phase(self, position, velocity, ai, playerPos, dt)
    end
end