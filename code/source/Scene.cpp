/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/

#include "Scene.hpp"

namespace MeshLoaderExercise
{
    Scene::Scene(const unsigned int _width, const unsigned int _height) :
        width  (_width), 
        height (_height),
        color_buffer(_width, _height),
        rasterizer(color_buffer)
    {
        model_a = make_shared< Model >(*this, "../../shared/assets/stanford-bunny.obj", "model_a");
        models.push_back(model_a);
    }

    void Scene::update ()
    {
        for (int i = 0; i <= models.size() - 1; i++)
        {
            auto mesh = models[i].get()->get_meshes();
            for (int j = 0; j <= mesh.size() - 1; j++)
            {
                mesh[j].update_mesh();
            }
        }
    }

    void Scene::render ()
    {
        for (int i = 0; i <= models.size() - 1; i++)
        {
            auto mesh = models[i].get()->get_meshes();
            for (int j = 0; j <= mesh.size() - 1; j++)
            {
                mesh[j].draw_mesh();
            }
        }
    }



}
