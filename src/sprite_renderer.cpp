#include "sprite_renderer.h"

#include <vector>
#include <iostream>

using namespace asteroidish;

SpriteRenderer::SpriteRenderer(Shader &shader) {
    this->shader = shader;
    this->init_render_data();
}

SpriteRenderer::~SpriteRenderer() {
    for (int i = 0; i < (int)this->VAOs.size(); i++) {
        glBindVertexArray(*this->VAOs[i]);
        glDeleteVertexArrays(1, this->VAOs[i]);
    }
}

void SpriteRenderer::init_render_data() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

// Initializes the VBO and VAO for a given game object.
void SpriteRenderer::init_vertex_data(float* vertices,
                                      int vertices_size,
                                      GLuint& VBO,
                                      GLuint& VAO) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->VAOs.push_back(&VAO);
}

void SpriteRenderer::draw_sprite(glm::vec2 position,
                                 GLuint VAO,
                                 int vertices_size,
                                 glm::vec2 size,
                                 float rotate,
                                 glm::vec3 color) {
    // Prepare transformations
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
    this->shader.set_matrix4("model", model);
    this->shader.set_vector3f("spriteColor", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices_size / 8);
}