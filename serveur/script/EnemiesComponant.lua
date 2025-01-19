--[[
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemiesComponant.lua
--]]

SineMovement = {
    time = 0
}

function SineMovement:update(position, velocity, ai, dt)
    self.time = (self.time or 0) + dt
    velocity.y = math.floor(ai.amplitude * math.sin(self.time))
end

CircleMovement = {
    targetX = 500
}

function CircleMovement:update(position, velocity, ai, dt)
    if position.x <= self.targetX then
        velocity.x = 0
        velocity.y = 0
    end
end

PlayerChase = {}

function PlayerChase:update(position, velocity, ai, playerPos, dt)
    local dx = playerPos.x - position.x
    local dy = playerPos.y - position.y
    local distance = math.sqrt(dx * dx + dy * dy)

    if distance > 0 then
        velocity.x = math.floor((dx / distance) * ai.speed)
        velocity.y = math.floor((dy / distance) * ai.speed)
    end
end

VFormation = {}

function VFormation:update(position, velocity, ai, leaderPos, dt)
    -- if leaderPos then
    --     local angle = math.pi / 4
    --     local xOffset = math.cos(angle) * ai.spacing * ai.index
    --     local yOffset = math.sin(angle) * ai.spacing * ai.index

    --     if ai.index % 2 == 0 then
    --         yOffset = -yOffset
    --     end

    --     position.x = math.floor(leaderPos.x - xOffset)
    --     position.y = math.floor(leaderPos.y + yOffset)
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