/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#include "Scene.hpp"
#include <SFML/Window.hpp>

using namespace sf;
using namespace MeshLoaderExercise;

int main ()
{
    const unsigned int window_width  = 800u;
    const unsigned int window_height = 600u;

    // 1. Creo la ventana de aplicación
    Window window(VideoMode(window_width, window_height), "Mesh Loader", Style::Titlebar | Style::Close);

    window.setVerticalSyncEnabled (true);

    // 2. Creo la escena
    Scene scene(window_width, window_height);


    // 3. Creo un bucle de aplicación

    bool exit = false;

    do
    {
        // 3.1 Eventos de teclado (input)
        Event event;

        while (window.pollEvent (event))
        {
            if (event.type == Event::Closed) exit = true;
        }

        // 3.2 Update
        scene.update();

        // 3.3 Render
        scene.render();

        // 3.4 Lo muestro por pantalla
        window.display ();
        
    }
    while (!exit);

    return 0;
}
