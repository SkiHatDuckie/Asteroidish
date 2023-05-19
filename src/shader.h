#pragma once

namespace asteroidish {
    // This looks silly, but you need to add `const` twice, otherwise the compiler
    // will not know that variables are being used outside the namespace.
    const char* const vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char* const fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

    // Returns `0` if an error occured.
    unsigned int init_shader_program();
}