/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#pragma once

#include <Color_Buffer.hpp>

#include <cstdlib>
#include <vector>
#include <memory>

#include "math.hpp"
#include "Rasterizer.hpp"
#include "View.hpp"


namespace MeshLoaderExercise
{
    using  std::vector;
    using  std::shared_ptr;
    using  std::make_shared;

    using argb::Rgb888;
    using argb::Color_Buffer;

    class Mesh
    {

    private:

        //View* view;

        aiScene* scene;

        int window_width = 800u;
        int window_height = 600u;

        // Color
        typedef Color_Buffer< Rgb888 > Color_Buffer;

        // Vértices
        typedef Point4f               Vertex;
        typedef vector< Vertex >      Vertex_Buffer;
        typedef vector< Rgb888  >     Vertex_Colors;

        // Índices
        typedef vector< int    >      Index_Buffer;


    private:

        //static constexpr char base_file_path[] = "../../shared/assets/";

        Color_Buffer               color_buffer;
        Rasterizer< Color_Buffer > rasterizer;

        Vertex_Buffer     original_vertices;
        Vertex_Colors     original_colors;
        Vertex_Buffer     transformed_vertices;

        Index_Buffer      original_indices;

        vector< Point4i > display_vertices;

        // id
        int mesh_id;

    public:
        //Mesh(View* _view, int _id, vector< Vertex> vertices, vector< int > indices );
        Mesh(aiScene& scene, int _id);
        //Mesh(&Mesh());
        ~Mesh() = default;

    public:

        void setup_mesh();
        void draw();

    private:


        bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);

        float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }
    };

}

