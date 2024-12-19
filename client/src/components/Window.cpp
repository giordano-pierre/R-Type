/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#include "components/Window.hpp"

namespace rtype::client {

Window::Window(const std::string &fontPath, TupleUInt size,
               TupleUInt serverSize)
    : _size(size), _serverSize(serverSize) {
    initGeneralInput(_inputConfig.first);
    initPlay1Input(_inputConfig);
    initPlay2Input(_inputConfig);
    sf::Font tmp = sf::Font();
    tmp.loadFromFile(fontPath);
    _font = std::make_shared<sf::Font>(tmp);
    // _shader.loadFromMemory(
    //         R"(
    //         uniform sampler2D texture;
    //         void main()
    //         {
    //             vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    //             // Apply a color-blind friendly filter (Protanopia example)
    //             float r = 0.567 * pixel.r + 0.433 * pixel.g;
    //             float g = 0.558 * pixel.r + 0.442 * pixel.g;
    //             float b = pixel.b;

    //             gl_FragColor = vec4(r, g, b, pixel.a);
    //         }
    //         )",
    //         sf::Shader::Fragment);

}

} // namespace rtype::client

std::ostream &operator<<(std::ostream &out,
                         const rtype::client::Window &window) {
    out << "size: " << window._size.x << " " << window._size.y << std::endl;
    out << "serverSize: " << window._serverSize.x << " "
        << window._serverSize.y;
    return out;
}
