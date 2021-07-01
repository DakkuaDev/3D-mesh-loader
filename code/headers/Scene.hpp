/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <Color_Buffer.hpp>

#include "Rasterizer.hpp"
#include "Model.hpp"
#include "Mesh.hpp"

#include <memory>
#include <vector>
#include <string>

using namespace std;
using namespace argb;

namespace MeshLoaderExercise
{
    class Model;
    class Scene
    {
    private:

        typedef Rgb888                Color;
        typedef Color_Buffer< Color > Color_Buffer;

    private:

        Color_Buffer               color_buffer;
        Rasterizer< Color_Buffer > rasterizer;

        vector<shared_ptr<Model>> models;

        unsigned int width;
        unsigned int height;

        // Modelos
        shared_ptr< Model > model_a;



    public:


        Scene(const unsigned int _width, const unsigned int _height);

        void update ();
        void render ();

    public:

        inline unsigned int get_width() { return width; }
        inline unsigned int get_height() { return height; }

        inline Rasterizer< Color_Buffer > get_rasterizer() { return rasterizer; }
    };

}

#endif
