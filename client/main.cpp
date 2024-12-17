#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "UDPClient.hpp"
#include "ECS/ECS.hpp"
#include "ClientHandlerSystem.hpp"

class Gui
{
public:
    Gui(const std::string& framesPath, int frameCount, int frameDurationMs)
        : m_frameCount(frameCount), m_frameDuration(sf::milliseconds(frameDurationMs)), m_currentFrame(0)
    {
        for (int i = 1; i < frameCount; ++i)
        {
            sf::Texture texture;
            std::string filename = framesPath + "/frame-" + std::to_string(i) + ".png";
            if (!texture.loadFromFile(filename))
            {
                std::cerr << "Erreur de chargement de l'image: " << filename << std::endl;
                continue;
            }
            m_frames.push_back(texture);
        }

        if (!m_frames.empty())
        {
            m_sprite.setTexture(m_frames[0]);
        }
    }

    void run()
    {
        sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Lunar Pirate GUI", sf::Style::Fullscreen);

        sf::Clock clock;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                {
                    window.close();
                }
                else if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (clock.getElapsedTime() > m_frameDuration)
            {
                m_currentFrame = (m_currentFrame + 1) % m_frames.size();
                m_sprite.setTexture(m_frames[m_currentFrame]);
                clock.restart();
            }

            sf::Vector2u windowSize = window.getSize();
            sf::Vector2u textureSize = m_frames[m_currentFrame].getSize();
            m_sprite.setScale(
                static_cast<float>(windowSize.x) / textureSize.x,
                static_cast<float>(windowSize.y) / textureSize.y
            );

            window.clear();
            window.draw(m_sprite);
            window.display();
        }
    }

private:
    std::vector<sf::Texture> m_frames;
    sf::Sprite m_sprite;
    int m_frameCount;
    sf::Time m_frameDuration;
    int m_currentFrame;
};

int main()
{
    // Gui gui("../assets/graphisme/lunar_pirate.gif", 49, 30);
    // gui.run();

    try {
        ECS ecs;
        ClientHandlerSystem client_handler;
        UDPClient client(ecs, "127.0.0.1", "4242");
        ecs.register_event<RequestEvent>();
        ecs.register_event<ReceiveEvent>();
        ecs.subscribe<RequestEvent>(client);
        ecs.subscribe<ReceiveEvent>(client_handler);
        ecs.post<RequestEvent>({NetworkActions::CONNECT, {"action", "connect"}});
        while(true) {
            if (!ecs.empty()) {
                auto &callback = ecs.front();
                callback();
                ecs.pop_front();
            }
        };
        while(true) {};
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
