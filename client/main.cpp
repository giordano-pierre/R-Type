#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <string>

class Gui
{
public:
    Gui(const std::string& framesPath, int frameCount, int frameRate)
        : m_frameCount(frameCount), m_frameRate(frameRate), m_currentFrame(0)
    {
        for (int i = 0; i < frameCount; ++i)
        {
            sf::Texture texture;
            std::string filename = framesPath + "/frame_" + std::to_string(i) + ".png";
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
        window.setFramerateLimit(m_frameRate);

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

            if (clock.getElapsedTime().asSeconds() > 1.0f / m_frameRate)
            {
                m_currentFrame = (m_currentFrame + 1) % m_frameCount;
                m_sprite.setTexture(m_frames[m_currentFrame]);
                clock.restart();
            }

            window.clear();
            window.draw(m_sprite);
            window.display();
        }
    }

private:
    std::vector<sf::Texture> m_frames;
    sf::Sprite m_sprite;
    int m_frameCount;
    int m_frameRate;
    int m_currentFrame;
};

int main()
{
    Gui gui("frames", 10, 12);
    gui.run();

    return 0;
}
