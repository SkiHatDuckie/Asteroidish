#pragma once

#include <map>
#include <string>

#include <glad/gl.h>

#include "shader.h"

namespace asteroidish {
    // A static singleton ResourceManager class that hosts several
    // functions to load Textures and Shaders. Each loaded texture
    // and/or shader is also stored for future reference by string
    // handles. All functions and resources are static and no 
    // public constructor is defined.
    class ResourceManager {
        public:
            // Resource storages
            static std::map<std::string, Shader> shaders;
            // Loads (and generates) a shader program from file loading vertex,
            // fragment (and geometry) shader's source code.
            // If gShaderFile is not nullptr, it also loads a geometry shader
            static Shader load_shader(const char *v_shader_file,
                                      const char *f_shader_file,
                                      const char *g_shader_file,
                                      std::string name);
            // Retrieves a stored shader
            static Shader get_shader(std::string name);
            // Properly de-allocates all loaded resources
            static void clear();
        private:
            // Private constructor, that is we do not want any actual resource manager objects.
            // Its members and functions should be publicly available (static).
            ResourceManager() { }
            // Loads and generates a shader from file
            static Shader load_shader_from_file(const char *v_shader_file,
                                                const char *f_shader_file,
                                                const char *g_shader_file = nullptr);
    };
}