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

