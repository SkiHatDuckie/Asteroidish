#pragma once

#include "game_object.h"

namespace asteroidish {
    class Ship : public GameObject {
        public:
            static float vertices[];
            static int vertices_size;
            static GLuint VBO, VAO;

            Ship();
            Ship(glm::vec2 pos,
                 glm::vec2 size,
                 glm::vec3 color = glm::vec3(1.0f),
                 glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

            void draw(SpriteRenderer &renderer) override;
    };
}