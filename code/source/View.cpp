/*
* @Author: Daniel Guerra Gallardo
* @Description: Programa de renderizado 3D de mayas poligonales
* @Date: 06/2021
*/


#include "View.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>


namespace MeshLoaderExercise
{
    View::View(int _width, int _height) : width (_width), height (_height)
    {
        const aiScene* scene;
        Assimp::Importer importer;

        scene = importer.ReadFile
        (
            "../../shared/assets/island.obj",
            aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
        );

        shared_ptr<Mesh> test_mesh = make_shared<Mesh>(scene, 0);
        test_mesh->draw();     
    }

    void View::update ()
    {
        //// Se actualizan los parámetros de transformatión (sólo se modifica el ángulo):

        ////static float angle = 0.f;

        ////angle += 0.025f;

        //// Se crean las matrices de transformación:

        //Matrix44 identity(1);
        ////Matrix44 scaling     = scale           (identity, 4.f);
        //Matrix44 scaling     = scale           (identity, 0.1f);
        ////Matrix44 rotation_y  = rotate_around_y (identity, angle);
        //Matrix44 translation = translate       (identity, Vector3f{ -2.5f, 8.f, -10.f });
        //Matrix44 projection  = perspective     (20, 1, 15, float(width) / height);

        //// Creación de la matriz de transformación unificada:

        ////Matrix44 transformation = projection * translation * rotation_y * scaling;
        //Matrix44 transformation = projection * translation * scaling;

        //// Se transforman todos los vértices usando la matriz de transformación resultante:

        //for (size_t index = 0, number_of_vertices = original_vertices.size (); index < number_of_vertices; index++)
        //{
        //    // Se multiplican todos los vértices originales con la matriz de transformación y
        //    // se guarda el resultado en otro vertex buffer:

        //    Vertex & vertex = transformed_vertices[index] = transformation * original_vertices[index];

        //    // La matriz de proyección en perspectiva hace que el último componente del vector
        //    // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

        //    float divisor = 1.f / vertex.w;

        //    vertex.x *= divisor;
        //    vertex.y *= divisor;
        //    vertex.z *= divisor;
        //    vertex.w  = 1.f;
        //}
    }

    void View::render ()
    {

    }



}
