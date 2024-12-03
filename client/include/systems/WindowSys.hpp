/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WindowSys
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <utility>

#include "SparseArray/SparseArray.hpp"
#include "ECS/ECS.hpp"
#include "components/Drawable.hpp"
#include "components/Position.hpp"
#include "events/FrameEvent.hpp"

namespace Rtype::Client{
    class WindowSys {
    public:
        WindowSys(sf::VideoMode mode, const sf::String &title,
                  sf::Uint32 style = 7U,
                  const sf::ContextSettings &settings = sf::ContextSettings());
        ~WindowSys() = default;

        void operator()(ECS &ecs, const FrameEvent &e_frame,
                        const SparseArray<Position> &positions,
                        SparseArray<Drawable> &sprites);

    private:
        sf::RenderWindow _window;
    };
}
