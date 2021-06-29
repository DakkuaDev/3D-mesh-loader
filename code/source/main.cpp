/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#include "View.hpp"
#include "Mesh.hpp"

#include <SFML/Window.hpp>

#include <memory>

using namespace sf;
using namespace MeshLoaderExercise;

int main ()
{
    // Create the window and the view that will be shown within the window:

    const unsigned int window_width  = 800u;
    const unsigned int window_height = 600u;

    Window window(VideoMode(window_width, window_height), "Mesh Loader", Style::Titlebar | Style::Close);
    View   view  (window_width, window_height);

    Mesh   mesh  (view);

    //mesh.load_mesh("../../shared/assets/stanford-bunny.obj");

    window.setVerticalSyncEnabled (true);

    // Run the main loop:

    bool exit = false;

    do
    {
        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed) exit = true;
        }

        //view.update ();
        mesh.update();

        //view.render ();
        mesh.render();

        window.display ();
        
    }
    while (!exit);

    return 0;
}
