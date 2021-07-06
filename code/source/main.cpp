/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#include "View.hpp"
#include <SFML/Window.hpp>

using namespace sf;
using namespace example;

int main ()
{
    // Create the window and the view that will be shown within the window:

    constexpr auto window_width  = 500u;
    constexpr auto window_height = 500u;

    float camera_speed = 0.1f;

    Window window(VideoMode(window_width, window_height), "Mesh Loader", Style::Titlebar | Style::Close);
    View   view  (window_width, window_height);

    window.setVerticalSyncEnabled (true);

    // Run the main loop:

    bool exit = false;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed) exit = true;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                // Camera Movement (Click derecho del ratón + WASD
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Arriba
                    view.get_camera()->move(0, -camera_speed, 0);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    // Abajo
                    view.get_camera()->move(0, camera_speed, 0);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    // Derecha
                    view.get_camera()->move(camera_speed, 0, 0);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    // Izquierda
                    view.get_camera()->move(-camera_speed, 0, 0);
                }
            }
            else
            {
                // Camera Rotation (WASD)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    // Vertical Positiva
                    view.get_camera()->rotate_x(camera_speed);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    // Vertical Negativa
                    view.get_camera()->rotate_x(-camera_speed);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    // Horizontal Positiva
                    view.get_camera()->rotate_y(camera_speed);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    // Horizontal Negativa
                    view.get_camera()->rotate_y(-camera_speed);
                }
            }         
        }

        view.update ();

        view.render ();

        window.display ();
    }
    while (not exit);

    return 0;
}
