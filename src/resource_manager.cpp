#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace asteroidish;

// Instantiate static variables
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::load_shader(const char *v_shader_file,
                                    const char *f_shader_file,
                                    const char *g_shader_file,
                                    std::string name) {
    shaders[name] = load_shader_from_file(v_shader_file, f_shader_file, g_shader_file);
    return shaders[name];
}

Shader ResourceManager::get_shader(std::string name) {
    return shaders[name];
}

void ResourceManager::clear() {
    // Properly delete all shaders	
    for (auto iter : shaders) {
        glDeleteProgram(iter.second.ID);
    }
}

Shader ResourceManager::load_shader_from_file(const char *v_shader_file,
                                              const char *f_shader_file,
                                              const char *g_shader_file) {
    // Retrieve the vertex/fragment source code from filePath
    std::string vertex_code;
    std::string fragment_code;
    std::string geometry_code;
    try {
        // Open files
        std::ifstream vertex_shader_file(v_shader_file);
        std::ifstream fragment_shader_file(f_shader_file);
        std::stringstream v_shader_stream, f_shader_stream;
        // Read file's buffer contents into streams
        v_shader_stream << vertex_shader_file.rdbuf();
        f_shader_stream << fragment_shader_file.rdbuf();
        // Close file handlers
        vertex_shader_file.close();
        fragment_shader_file.close();
        // Convert stream into string
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
        // If geometry shader path is present, also load a geometry shader
        if (g_shader_file != nullptr) {
            std::ifstream geometry_shader_file(g_shader_file);
            std::stringstream g_shader_stream;
            g_shader_stream << geometry_shader_file.rdbuf();
            geometry_shader_file.close();
            geometry_code = g_shader_stream.str();
        }
    }
    catch (std::exception const&) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *v_shader_code = vertex_code.c_str();
    const char *f_shader_code = fragment_code.c_str();
    const char *g_shader_code = geometry_code.c_str();
    // Now create shader object from source code
    Shader shader;
    shader.compile(v_shader_code,
                   f_shader_code,
                   g_shader_file != nullptr ? g_shader_code : nullptr);
    return shader;
}