/*
* @Author: Daniel Guerra Gallardo
* @Date: 07/2021
* @Description: 3D mesh loader exercise
* daniel.guerra.gallardo99@gmail.com
*/

#pragma once

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "math.hpp"
#include <string>

using namespace std;

namespace MeshLoader
{
    class EntityTrasform
    {
    private:

        EntityTrasform* parent = nullptr;

        Matrix44 identity;

        Matrix44 translation;

        Matrix44 scaling;

        Matrix44 rotation_x;
        Matrix44 rotation_y;
        Matrix44 rotation_z;

        string id;

    public:
        EntityTrasform(string id);
        ~EntityTrasform() = default;

    public:

        void traslate_entity(float x, float y, float z);

        void rotate_entity_x(float angle);
        void rotate_entity_y(float angle);
        void rotate_entity_z(float angle);

        void scale_entity(float scale_factor);

        Matrix44 update_trasform(Matrix44 projection);

        inline void set_parent(EntityTrasform& new_parent) { parent = &new_parent; }
    };
}

#endif

