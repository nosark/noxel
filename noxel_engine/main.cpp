// noxel_engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Created by Kyle Nosar on 1/9/23

#include <iostream>

#include "FileOps.h"
#include "Renderer.h"
#include "Shader.h"

struct Vertex {
    float x;
    float y;
    float z;
};

int main() {
    
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Noxel Engine", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Load glad and verify success
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "FAILED TO INITIALIZE GLAD! \n Please make sure glad is loaded properly..." << std::endl;
        return -1;
    }

    Vertex vertices[] = {
        Vertex { 0.5f, 0.5f, 0.0f }, //top right
        Vertex { 0.5f, -0.5f, 0.0f }, //bottom right 
        Vertex { -0.5f, -0.5f, 0.0f }, // bottom left
        Vertex { -0.5f, 0.5f, 0.0f }, //top left
    };

    // drawing order for the element buffer
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };

    // Create our basic shader program
    Shader* basic_shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");

    // Create vertex buffer 
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //init vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // create element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    // bind and buffer EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind buffer and prep data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Bind again unbinds this vao so other VAO calls won't use this array 
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //use shader_program
        basic_shader->bind();
        glBindVertexArray(VAO);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Cleanup
    delete basic_shader;
    glfwTerminate();
    return 0;
}

