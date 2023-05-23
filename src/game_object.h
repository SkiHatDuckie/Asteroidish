#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "sprite_renderer.h"

namespace asteroidish {
    // Container object for holding all state relevant for a single
    // game object entity. Each object in the game likely needs the
    // minimal of state as described within GameObject.
    class GameObject {
        public:
            // Object state
            glm::vec2 position, size, velocity;
            glm::vec3 color;
            float rotation;
            bool is_solid;
            bool destroyed;
            // Constructor(s)
            GameObject();
            GameObject(glm::vec2 pos,
                       glm::vec2 size,
                       glm::vec3 color = glm::vec3(1.0f),
                       glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
            // draw sprite
            virtual void draw(SpriteRenderer &renderer);
    };
}