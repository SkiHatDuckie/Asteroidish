#include "ship.h"

using namespace asteroidish;

float Ship::vertices[] = {
    // Postions          // Colors
    -0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.0f , -0.4f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.0f ,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
};
unsigned int Ship::indices[] = {
    0, 1, 2,
    3, 1, 2
};
int Ship::vertices_size = sizeof(Ship::vertices);
int Ship::indices_size = sizeof(Ship::indices);

float* Ship::get_vertices() {
    return Ship::vertices;
}

int Ship::get_vertices_size() {
    return Ship::vertices_size;
}

unsigned int* Ship::get_indices() {
    return Ship::indices;
}

int Ship::get_indices_size() {
    return Ship::indices_size;
}