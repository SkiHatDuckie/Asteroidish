#include "sprite_renderer.h"

#include <iostream>

using namespace asteroidish;

SpriteRenderer::SpriteRenderer(Shader &shader) {
    this->shader = shader;
    this->init_render_data();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::init_render_data() {
    // Configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
         0.25f,  0.5f,
         0.0f ,  0.4f,
         0.0f , -0.5f,

        -0.25f,  0.5f,
         0.0f ,  0.4f,
         0.0f , -0.5f,
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void SpriteRenderer::draw_sprite(glm::vec2 position,
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

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}