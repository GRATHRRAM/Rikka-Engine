#include "rikka_core.h"
#include "rikka_datatypes.h"

float vertices[] = {
    -1.0, -1.0, 0.0,
     0.0, -1.0, 0.0,
     -0.25,0.0, 0.0,

     1, 1, 0,
     0 ,1, 0,
     0.25,0,0
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
    3,4,5
};

const char * vertexshader = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

const char *fragmentshader = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"   FragColor = vec4(1.0,0.5,0.2,1.0);\n"
"}\n";

int main(void) {
    rkk_InitGLFW();

    rkk_Window *Window = rkk_GetWindow(800,600,"Lerning OpenGL");

    rkk_UseWindow(Window);
    rkk_InitGLEW();
    
    rkk_SetDebug(rkk_enable);
    rkk_SetVsync(rkk_enable);

    /*OpenGL*/

    GLuint VBO;
    glGenBuffers(1, &VBO);//ALLOC VBO IN GRAPHICS CARD
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//USE IT?
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//COPY vertex to VBO
                                                                              
    GLuint ShaderProgram = rkk_CreateShaderProgram(vertexshader,fragmentshader);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /*OpenGL*/

    while (!rkk_WindowShouldClose(Window)) {
    
        rkk_Clear(rkk_MakeColorU8(0,0,0,255));

        glUseProgram(ShaderProgram);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        rkk_SwapBuffers(Window);
        rkk_PollEvents();
    }

    return 0;
}
