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

    constexpr auto window_width  = 800u;
    constexpr auto window_height = 600u;

    int camera_speed = 1;

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

            switch (event.type == Event::KeyPressed)
            {
            case sf::Keyboard::W :
                view.get_camera()->move(0, 0, -camera_speed);
                break;

            case sf::Keyboard::A :
                view.get_camera()->move(-camera_speed, 0, 0);
                break;

            case sf::Keyboard::S :
                view.get_camera()->move(0, 0, camera_speed);
                break;

            case sf::Keyboard::D :
                view.get_camera()->move(camera_speed, 0, 0);
                break;
            default:
                break;
            }
        }

        view.update ();

        view.render ();

        window.display ();
    }
    while (not exit);

    return 0;
}
