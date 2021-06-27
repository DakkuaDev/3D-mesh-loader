/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "Mesh.hpp"

using namespace std;

namespace MeshLoaderExercise
{

    class Mesh;
    class View
    {
    private:

        //static unsigned width;
        //static unsigned height;

        //Mesh* tree_mesh;

        int width;
        int height;

    public:


        //static View& getInstance()
        //{
        //    static View instance(width, height); // Guaranteed to be destroyed.
        //                          // Instantiated on first use.
        //    return instance;
        //}

        View(int _width, int _height);

        void update ();
        void render ();

    public:

        inline unsigned get_width() { return width; }
        inline unsigned get_height() { return height; }       
    };

}

#endif
