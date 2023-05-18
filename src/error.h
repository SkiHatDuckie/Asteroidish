#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace asteroidish {
    void error_callback(int error, const char* description);
    void init_error();
}