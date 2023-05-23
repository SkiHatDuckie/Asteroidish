#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "shader.h"

namespace asteroidish {
    class SpriteRenderer {
        public:
            SpriteRenderer(Shader &shader);
            ~SpriteRenderer();

            void init_vertex_data(float* vertices, int vertices_size, GLuint& VBO, GLuint& VAO);
            void draw_sprite(glm::vec2 position,
                             GLuint VAO,
                             int vertices_size,
                             glm::vec2 size = glm::vec2(10.0f, 10.0f),
                             float rotate = 0.0f,
                             glm::vec3 color = glm::vec3(1.0f));
        private:
            Shader shader;
            std::vector<GLuint*> VAOs;

            void init_render_data();
    };
}