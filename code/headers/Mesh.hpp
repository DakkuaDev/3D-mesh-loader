/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/


#ifndef MESH_HEADER
#define MESH_HEADER

#include "View.hpp"

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace argb;
using namespace Assimp;

namespace MeshLoaderExercise
{
    class View;
    class Mesh
    {
    private:

        typedef Rgb888                Color;
        //typedef Color_Buffer< Color > Color_Buffer;
        typedef Point4f               Vertex;
        typedef vector< Vertex >      Vertex_Buffer;
        typedef vector< int    >      Index_Buffer;
        typedef vector< Color  >      Vertex_Colors;

    private:

        View* view;
        vector<int> m_entries;

        const std::string& base_path = "../../shared/assets/";


        Vertex_Buffer     original_vertices;
        Index_Buffer      original_indices;
        Vertex_Colors     original_colors;
        Vertex_Buffer     transformed_vertices;
        vector< Point4i > display_vertices;

    public:

        Mesh(View& _view);

        bool load_mesh(const std::string& filename);
        bool init_from_scene(const aiScene* pScene, const std::string& Filename);

        void init_mesh(const aiMesh* paiMesh);

        void update();
        void render();

    private:

        bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
        float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }

    };

}

#endif

//#pragma once
//
//#include <Color_Buffer.hpp>
//
//#include <cstdlib>
//#include <vector>
//#include <memory>
//
//#include "math.hpp"
//#include "Rasterizer.hpp"
//#include "View.hpp"
//
//
//namespace MeshLoaderExercise
//{
//    using  std::vector;
//    using  std::shared_ptr;
//    using  std::make_shared;
//
//    using argb::Rgb888;
//    using argb::Color_Buffer;
//
//    class Mesh
//    {
//
//    private:
//
//        //View* view;
//
//        aiScene* scene;
//
//        int window_width = 800u;
//        int window_height = 600u;
//
//        // Color
//        typedef Color_Buffer< Rgb888 > Color_Buffer;
//
//        // Vértices
//        typedef Point4f               Vertex;
//        typedef vector< Vertex >      Vertex_Buffer;
//        typedef vector< Rgb888  >     Vertex_Colors;
//
//        // Índices
//        typedef vector< int    >      Index_Buffer;
//
//
//    private:
//
//        //static constexpr char base_file_path[] = "../../shared/assets/";
//
//        Color_Buffer               color_buffer;
//        Rasterizer< Color_Buffer > rasterizer;
//
//        Vertex_Buffer     original_vertices;
//        Vertex_Colors     original_colors;
//        Vertex_Buffer     transformed_vertices;
//
//        Index_Buffer      original_indices;
//
//        vector< Point4i > display_vertices;
//
//        // id
//        int mesh_id;
//
//    public:
//        //Mesh(View* _view, int _id, vector< Vertex> vertices, vector< int > indices );
//        Mesh(aiScene& scene, int _id);
//        //Mesh(&Mesh());
//        ~Mesh() = default;
//
//    public:
//
//        void setup_mesh();
//        void draw();
//
//    private:
//
//
//        bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
//
//        float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }
//    };
//
//}

