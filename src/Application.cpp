#include "imgui.h"
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "Shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(void) {

    /* Window */

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Vertex Shader */

    Shader ourShader("res/shaders/Vertex.shader",
                     "res/shaders/Fragment.shader");

    /* Vertecies */

    float vertices[] = {
        // positions                        // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    float verticesB[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        1.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.75f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // top
    };

    unsigned int VBOB;
    unsigned int VAOB;
    unsigned int VBO;
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAOB);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBOB);

    //

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //

    glBindVertexArray(VAOB);
    glBindBuffer(GL_ARRAY_BUFFER, VBOB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /* Main Loop */

    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // rendering commands here
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw

        ourShader.use();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOB);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
