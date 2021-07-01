#pragma once


#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Scene.hpp"
#include "Mesh.hpp"


#ifndef MODEL_HEADER
#define MODEL_HEADER

namespace MeshLoaderExercise
{
    class Scene;
    class Mesh;
    class Model
    {
    private:

        shared_ptr< Scene > scene;

        vector<Mesh> meshes;

        string directory;
        string id;

    public:
        Model(Scene& _scene, const char* _path, const string& _id) : scene (&_scene), id (_id)
        {
            load_model(_path);
        }
        void draw_model();

    public:
        inline Scene* get_scene() { return scene.get(); }
        inline string& get_id() { return id; }
        inline vector<Mesh>& get_meshes() { return meshes; }

    private:
        void load_model(string _path);
        void process_node(aiNode* node, const aiScene* scene);
        Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
      
    };
}

#endif


