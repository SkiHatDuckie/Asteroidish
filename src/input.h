#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace asteroidish {
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void init_input(GLFWwindow* window);
}