#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

#include "error.h"
#include "input.h"
#include "shader.h"
#include "ship.h"

// Used to properly resize the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    // GLFW: Initialize/Configure
    asteroidish::init_error();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,
                                          SCR_HEIGHT,
                                          "Asteroidish",
                                          NULL,
                                          NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    // Open all OpenGL function pointers with glad
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build and compile shader program
    asteroidish::Shader shaderProgram = asteroidish::Shader("shader.vs", "shader.fs");

    // Set up vertex data and buffer(s) and configure vertx attributes
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Initialize game objects and Asteroidish modules
    asteroidish::init_input(window);
    asteroidish::Ship ship = asteroidish::Ship();

    // Bind vertex array, then bind an set the vertex buffer(s),
    // then configure attributes.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 ship.get_vertices_size(),
                 ship.get_vertices(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 ship.get_indices_size(),
                 ship.get_indices(),
                 GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw wireframe shapes
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Update window
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ship
        shaderProgram.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,
                       ship.get_indices_size() / 4,
                       GL_UNSIGNED_INT,
                       0);
        glBindVertexArray(0);

        // GLFW: Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}