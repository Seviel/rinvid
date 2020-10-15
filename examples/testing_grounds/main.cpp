#include <SFML/Window.hpp>

#include "core/include/rinvid_gfx.h"
#include "core/include/triangle_shape.h"
#include "util/include/vector3.h"

void handle_events(sf::Window& window, sf::Event& event);

int main()
{
    sf::Window window(sf::VideoMode(800, 600), "Rinvid testing grounds");
    rinvid::RinvidGfx::set_viewport(0, 0, 800, 600);

    sf::Event event;

    window.setActive(true);

    rinvid::TriangleShape triangle{rinvid::Vector3{-0.8F, -0.5F, 0.0F},
                                   rinvid::Vector3{0.8F, -0.5F, 0.0F},
                                   rinvid::Vector3{0.0F, 0.8F, 0.0F}};

    while (window.isOpen())
    {
        handle_events(window, event);

        rinvid::RinvidGfx::clear_screen(0.2F, 0.4F, 0.4F, 1.0F);

        triangle.draw();

        window.display();
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
            default:
                break;
        }
    }
}