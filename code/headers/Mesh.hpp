/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/


#ifndef MESH_HEADER
#define MESH_HEADER


#include "Model.hpp"

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace argb;
using namespace Assimp;

namespace MeshLoaderExercise
{
    class Model;
    class Mesh
    {
    private:

        shared_ptr<Model> model;

        typedef Rgb888                Color;

        typedef Point4f               Vertex;
        typedef vector< Vertex >      Vertex_Buffer;
        typedef vector< int    >      Index_Buffer;

        typedef vector< Color  >      Vertex_Colors;

    private:

        Vertex_Buffer     original_vertices;
        Index_Buffer      original_indices;
        Vertex_Colors     original_colors;
        Vertex_Buffer     transformed_vertices;
        vector< Point4i > display_vertices;

    public:

        Mesh(Model& _model)
        {
            model = make_shared<Model>(_model);
        };

        void init_mesh(const aiMesh* paiMesh);

        void update_mesh();
        void draw_mesh();

    private:

        bool  is_frontface(const Vertex* const projected_vertices, const int* const indices);
        float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }

    };

}

#endif


