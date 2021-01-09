/**********************************************************************
 * Copyright (c) 2021, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include <unistd.h>

#include <SFML/Window.hpp>

#include "core/include/rectangle_shape.h"
#include "core/include/sprite.h"
#include "core/include/texture.h"
#include "util/include/vector2.h"

void handle_events(sf::Window& window, sf::Event& event);

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "Rinvid texture testing");
    rinvid::RinvidGfx::set_viewport(0, 0, 800, 600);

    sf::Event event;

    window.setActive(true);

    rinvid::RinvidGfx::init();

    rinvid::Texture texture{
        "/home/seviel/Desktop/rinvid/examples/texture_messing_around/res/logo.png"};
    rinvid::Sprite sprite{&texture, 100, 100, rinvid::Vector2{0.0F, 0.0F}};

    rinvid::RectangleShape rectangle{rinvid::Vector2{350.0F, 35.0F}, 100.0F, 50.0F};
    rectangle.set_color(rinvid::Color{0.2F, 0.2F, 0.8F, 1.0F});

    while (window.isOpen())
    {
        handle_events(window, event);

        rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);

        /// @todo implementation

        sprite.draw();

        rectangle.draw();

        sprite.set_position(rinvid::Vector2{350.0F, 250.0F});

        window.display();

        usleep(10000);
    }

    return 0;
}

void handle_events(sf::Window& window, sf::Event& event)
{
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                rinvid::RinvidGfx::set_viewport(0, 0, event.size.width, event.size.height);
                break;
            case sf::Event::KeyPressed:
                window.close();
            default:
                break;
        }
    }
}
