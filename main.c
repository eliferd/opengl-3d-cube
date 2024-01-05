#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "window.h"
#include "shader.h"
#include "camera.h"
#include <cglm.h>

int main()
{
    init_window();

    printf("GLAD : %d\n", gladLoadGL());
    printf("OpenGL Version : %s\n", glGetString(GL_VERSION));
    printf("Renderer (GPU) : %s", glGetString(GL_RENDERER));

    init_shaders();

    render_loop();

    return 0;
}

void render_loop()
{
    createCube();

    while(!glfwWindowShouldClose(get_window()))
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        renderCube();

        glDisable(GL_DEPTH_TEST);
        glfwPollEvents();
        glfwSwapBuffers(get_window());
    }

    glfwTerminate();
}

void createCube()
{
    float vertices[] = {
        // [POS]                [COLORS]
        // front
        -0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
         0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f,

         // left
        -0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,

        // back
        -0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,

        // right
         0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,

        // top
        -0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f,  0.5f,  0.5f,     1.0f, 0.5f, 0.31f,

         // bottom
        -0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f,
        -0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f, -0.5f, -0.5f,     1.0f, 0.5f, 0.31f,
         0.5f, -0.5f,  0.5f,     1.0f, 0.5f, 0.31f
    };

    unsigned int drawOrder[] = {
        // front
        0, 1, 2,
        2, 3, 0,

        // left
        4, 5, 6,
        6, 7, 4,

        // back
        8, 9, 10,
        10, 11, 8,

        // right
        12, 13, 14,
        14, 15, 12,

        // top
        16, 17, 18,
        18, 19, 16,

        // bottom
        20, 21, 22,
        22, 23, 20
    };

    // Declare buffers
    unsigned int VAO = 0,
                 VBO = 0,
                 EBO = 0;

    // Init buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind buffers data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawOrder), drawOrder, GL_STATIC_DRAW);

    // Set shader input attributes data
    int vPosInput = glGetAttribLocation(get_shader_program_id(), "vPosInput");
    int vColorInput = glGetAttribLocation(get_shader_program_id(), "vColorInput");

    glEnableVertexAttribArray(vPosInput);
    glVertexAttribPointer(vPosInput, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(vColorInput);
    glVertexAttribPointer(vColorInput, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Draw pixels
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void renderCube()
{
    sendMatricesToOpenGL(get_shader_program_id());

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, is_debug() ? GL_LINE : GL_FILL);
}

void createLightCube()
{

}
