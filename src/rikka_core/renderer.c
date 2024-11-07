#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../rikka_datatypes.h"
#include "../rikka_core.h"

extern const char* __RKK_RECT_VERTEX_GLSL;
extern const char* __RKK_RECT_FRAGMENT_GLSL;

rkk_Renderer rkk_GetRenderer();
void rkk_DestroyRenderer(rkk_Renderer *Rnd);
void rkk_Clear(rkk_Color Color);
void rkk_RndDrawRect(rkk_Renderer *Rnd, rkk_vec2 Position, rkk_vec2 Size, rkk_Color Color);

rkk_Renderer rkk_GetRenderer() {
    GLuint RectShader = rkk_CreateShaderProgram(__RKK_RECT_VERTEX_GLSL, __RKK_RECT_FRAGMENT_GLSL);
   
    rkk_Renderer rnd = {};
    rnd.RectShader = RectShader;

    return rnd;
}

void rkk_DestroyRenderer(rkk_Renderer *Rnd) {
    rkk_DeleteShaderProgram(Rnd->RectShader);
}

void rkk_Clear(rkk_Color Color) {
    glClearColor(Color.r, Color.g, Color.b, Color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void rkk_RndDrawRect(rkk_Renderer *Rnd, rkk_vec2 Pos, rkk_vec2 Size, rkk_Color Color) {
    // Define rectangle vertices (positions)
    GLfloat vertices[] = {
        // Positions (X, Y, Z)
        Pos.x,          Pos.y,          0.0f,  // Bottom-left
        Pos.x + Size.x, Pos.y,          0.0f,  // Bottom-right
        Pos.x + Size.x, Pos.y + Size.x, 0.0f,  // Top-right
        Pos.x,          Pos.y + Size.y, 0.0f   // Top-left
    };

    GLuint indices[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };

    // Create VAO, VBO, and EBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind and configure the Vertex Array Object
    glBindVertexArray(VAO);

    // Bind the vertex buffer and load data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind the element buffer and load data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Configure the position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Use the shader program
    glUseProgram(Rnd->RectShader);

    // Pass the color uniform to the shader
    GLint colorLoc = glGetUniformLocation(Rnd->RectShader, "rectColor");
    glUniform4f(colorLoc, Color.r, Color.g, Color.b, Color.a);

    // Draw the rectangle
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
