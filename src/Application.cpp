#include "glm/ext/matrix_transform.hpp"
#include "imgui.h"
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_NONE
#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
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

    Shader ourShader("res/shaders/rectangle/Vertex.shader",
                     "res/shaders/rectangle/Fragment.shader");

    /* Vertecies */

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float vertices[] = {
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    float verticesB[] = {
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    unsigned int VBO, VAO, EBO;
    unsigned int VBOB, VAOB, EBOB;

    //

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //

    glGenVertexArrays(1, &VAOB);
    glGenBuffers(1, &VBOB);
    glGenBuffers(1, &EBOB);

    glBindVertexArray(VAOB);

    glBindBuffer(GL_ARRAY_BUFFER, VBOB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /* Textrues */

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("res/textures/container.jpg", &width,
                                    &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    /* Main Loop */

    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // rendering commands here
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Transformation */

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans =
            glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        unsigned int transformLoc =
            glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        // Draw

        glBindTexture(GL_TEXTURE_2D, texture);
        ourShader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAOB);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
