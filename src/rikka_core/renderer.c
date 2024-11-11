#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../rikka_datatypes.h"
#include "../rikka_core.h"

extern const char* __RKK_RECT_VERTEX_GLSL;
extern const char* __RKK_RECT_FRAGMENT_GLSL;

rkk_Renderer rkk_GetRenderer(rkk_vec2 ScreenSize);
void rkk_DestroyRenderer(rkk_Renderer *Rnd);
void rkk_Clear(rkk_Color Color);
void rkk_RendererDrawShape(float *Vertex, rkk_u32 *Indices, GLuint ShaderProgram);
void rkk_RendererDrawRect(rkk_Renderer *Rnd, rkk_vec2 Position, rkk_vec2 Size, rkk_Color Color);

rkk_Renderer rkk_GetRenderer(rkk_vec2 ScreenSize) {
    GLuint RectShader = rkk_CreateShaderProgram(__RKK_RECT_VERTEX_GLSL, __RKK_RECT_FRAGMENT_GLSL);
   
    rkk_Renderer rnd = {};
    rnd.ScreenSize = ScreenSize;
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

void rkk_RendererDrawShape(float *Vertex, rkk_u32 *Indices, GLuint ShaderProgram) {

}

void rkk_RendererDrawRect(rkk_Renderer *Rnd, rkk_vec2 Pos, rkk_vec2 Size, rkk_Color Color) {
    GLfloat vertices[] = {
        Pos.x,          Pos.y,          0.0f,
        Pos.x + Size.x, Pos.y,          0.0f,
        Pos.x + Size.x, Pos.y + Size.y, 0.0f,
        Pos.x,          Pos.y + Size.y, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUseProgram(Rnd->RectShader);

    GLint colorLoc = glGetUniformLocation(Rnd->RectShader, "rectColor");
    glUniform4f(colorLoc, Color.r, Color.g, Color.b, Color.a);

    GLuint ScreenSizeLoc = glGetUniformLocation(Rnd->RectShader, "ScreenSize");
    glUniform3f(ScreenSizeLoc, Rnd->ScreenSize.x, Rnd->ScreenSize.y, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
