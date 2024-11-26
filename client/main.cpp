#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Gui
{
public:
    Gui(const std::string& framesPath, int frameCount, int frameDurationMs)
        : m_frameCount(frameCount), m_frameDuration(sf::milliseconds(frameDurationMs)), m_currentFrame(0)
    {
        for (int i = 0; i < frameCount; ++i)
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
    Gui gui("../assets/graphisme/lunar_pirate.gif", 48, 30);
    gui.run();

    return 0;
}
