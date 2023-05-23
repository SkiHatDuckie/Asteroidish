#include "ship.h"

#include <iostream>

using namespace asteroidish;

float Ship::vertices[] = {
     0.25f,  0.5f,
     0.0f ,  0.4f,
     0.0f , -0.5f,

    -0.25f,  0.5f,
     0.0f ,  0.4f,
     0.0f , -0.5f,
};
int Ship::vertices_size = sizeof(vertices);
GLuint Ship::VBO;
GLuint Ship::VAO;

Ship::Ship() {
    GameObject();
}

Ship::Ship(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity) {
    GameObject(pos, size, color, velocity);
}

void Ship::draw(SpriteRenderer &renderer) {
    renderer.draw_sprite(this->position, VAO, vertices_size, this->size, this->rotation, this->color);
}