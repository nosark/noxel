// noxel_engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <glad/glad.h>
//#include <GLFW/glfw3.h>\

#include "FileOps.h"
#include "Renderer.h"

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
    window = glfwCreateWindow(640, 480, "Hello Graphical World", nullptr, nullptr);
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
       -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };


    const std::string vertex_shader_file_path = "vertex_shader.glsl";
    std::string vertex_shader_src;
    const char* vertex_shader_source; // Shader source can't take string needs const char * 


    const std::string fragment_shader_file_path = "fragment_shader.glsl";
    std::string fragment_shader_src;
    const char* fragment_shader_source;

    FileOps::load_shader(vertex_shader_file_path, vertex_shader_src);
    vertex_shader_source = vertex_shader_src.c_str();

    FileOps::load_shader(fragment_shader_file_path, fragment_shader_src);
    fragment_shader_source = fragment_shader_src.c_str();


    // create shader object
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);


    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);

    glCompileShader(vertex_shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //create shader program object
    unsigned int shader_program = glCreateProgram();

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    //check shader program link success
    GL_CALL(glGetProgramiv(shader_program, GL_LINK_STATUS, &success));
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKAGE\n" << infoLog << std::endl;
    }

    // we've linked shaders to program, so delete them  now
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);


    // Create vertex buffer 
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    //init vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

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
        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

