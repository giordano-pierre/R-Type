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
    newY = ai.amplitude * math.sin(ai.frequency * self.time)
    position.y = math.floor(position.y + newY)
    position.x = math.floor(position.x - velocity.x)
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
