/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <Color_Buffer.hpp>

#include "Rasterizer.hpp"
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace argb;
using namespace Assimp;

namespace MeshLoaderExercise
{

    class Mesh;
    class View
    {
    private:

        typedef Rgb888                Color;
        typedef Color_Buffer< Color > Color_Buffer;

    private:

        Color_Buffer               color_buffer;
        Rasterizer< Color_Buffer > rasterizer;

        unsigned int width;
        unsigned int height;

    public:


        //static View& getInstance()
        //{
        //    static View instance(width, height); // Guaranteed to be destroyed.
        //                          // Instantiated on first use.
        //    return instance;
        //}

        View(const unsigned int _width, const unsigned int _height);

        void update ();
        void render ();

    public:

        inline unsigned int get_width() { return width; }
        inline unsigned int get_height() { return height; }

        inline Rasterizer< Color_Buffer > get_rasterizer() { return rasterizer; }
    };

}

#endif
