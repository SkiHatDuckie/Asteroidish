#include "error.h"
#include <cstdio>

void asteroidish::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void asteroidish::init_error() {
    glfwSetErrorCallback(&error_callback);
}