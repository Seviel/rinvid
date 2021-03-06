/**********************************************************************
 * Copyright (c) 2020 - 2021, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifdef __unix__
#include <unistd.h>
#else
#include <windows.h>
#endif

#include <chrono>

#include <SFML/Window.hpp>

#include "core/include/animation.h"
#include "core/include/circle_shape.h"
#include "core/include/quad_shape.h"
#include "core/include/rectangle_shape.h"
#include "core/include/rinvid_gfx.h"
#include "core/include/rinvid_gl.h"
#include "core/include/sprite.h"
#include "core/include/texture.h"
#include "core/include/triangle_shape.h"
#include "util/include/collision_detection.h"
#include "util/include/vector3.h"

/// Should be set to false when users attempts to close the app
static bool static_running = true;

void handle_events(sf::Window& window, sf::Event& event);

int main()
{
    std::chrono::duration<double> delta_time{};

    sf::Window window(sf::VideoMode(800, 600), "Rinvid testing grounds");
#ifdef _WIN32
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction));
#endif

    rinvid::RinvidGfx::set_viewport(0, 0, 800, 600);

    sf::Event event;

    window.setActive(true);

    rinvid::TriangleShape triangle{rinvid::Vector2<float>{400.0F, 200.0F},
                                   rinvid::Vector2<float>{300.0F, 100.0F},
                                   rinvid::Vector2<float>{500.0F, 100.0F}};
    triangle.set_color(rinvid::Color{0.1F, 0.8F, 0.3F, 1.0F});

    rinvid::QuadShape quad{
        rinvid::Vector2<float>{100.0F, 40.0F}, rinvid::Vector2<float>{150.0F, 40.0F},
        rinvid::Vector2<float>{160.0F, 90.0F}, rinvid::Vector2<float>{90.0F, 90.0F}};
    quad.set_color(rinvid::Color{0.8F, 0.1F, 0.3F, 1.0F});

    rinvid::RectangleShape rectangle{rinvid::Vector2<float>{350.0F, 35.0F}, 100.0F, 50.0F};
    rectangle.set_color(rinvid::Color{0.2F, 0.2F, 0.8F, 1.0F});
    rectangle.set_rotation(90.0F);

    rinvid::CircleShape circle{rinvid::Vector2<float>{500.0F, 300.0f}, 100.0F};
    circle.set_color(rinvid::Color{0.1F, 0.7F, 0.8F, 1.0F});

    rinvid::Texture texture{"examples/testing_grounds/resources/logo.png"};
    rinvid::Sprite  sprite{&texture, 100, 100, rinvid::Vector2<float>{200.0F, 200.0F},
                          rinvid::Vector2<float>{0.0F, 0.0F}};

    rinvid::Texture   clock_texture{"examples/testing_grounds/resources/clck.png"};
    rinvid::Sprite    clock_sprite{&clock_texture, 100, 100, rinvid::Vector2<float>{650.0F, 450.0F},
                                rinvid::Vector2<float>{0.0F, 0.0F}};
    auto              regions = clock_sprite.split_animation_frames(100, 100, 12, 1);
    rinvid::Animation clock_animation{20.0, regions, rinvid::AnimationMode::Looping};
    clock_sprite.add_animation("anim", clock_animation);
    clock_sprite.play("anim");
    clock_sprite.set_scale(1.5F);

    rinvid::RinvidGfx::init();

    bool quad_alive{true};

    while (static_running)
    {
        auto start = std::chrono::high_resolution_clock::now();

        handle_events(window, event);

        rinvid::RinvidGfx::clear_screen(0.1F, 0.2F, 0.2F, 1.0F);

        if (intersects(triangle.bounding_rect(), quad.bounding_rect()))
        {
            quad_alive = false;
        }

        triangle.draw();
        if (quad_alive)
        {
            quad.draw();
        }
        rectangle.draw();
        circle.draw();
        sprite.draw();
        clock_sprite.draw(delta_time.count());

        triangle.move(rinvid::Vector2<float>{1.0F, 0.0F});
        rinvid::Vector2<float> triangle_origin = triangle.get_origin();
        if (triangle_origin.x >= rinvid::RinvidGfx::get_width())
        {
            triangle.set_position(rinvid::Vector2<float>{0.0F, triangle_origin.y});
        }

        quad.move(rinvid::Vector2<float>{0.0F, 2.0F});
        rinvid::Vector2<float> quad_origin = quad.get_origin();
        if (quad_origin.y >= rinvid::RinvidGfx::get_height())
        {
            quad.set_position(rinvid::Vector2<float>{quad_origin.x, 0.0F});
        }

        sprite.rotate(0.5F);

        circle.scale(0.99F);

        window.display();

#ifdef __unix__
        usleep(10000);
#else
        Sleep(10);
#endif

        auto end   = std::chrono::high_resolution_clock::now();
        delta_time = end - start;
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
                static_running = false;
                break;
            case sf::Event::Resized:
                rinvid::RinvidGfx::set_viewport(0, 0, event.size.width, event.size.height);
                break;
            default:
                break;
        }
    }
}
