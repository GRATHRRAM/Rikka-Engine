#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "../rikka_datatypes.h"
#include "../rikka_core.h"

extern const char* __RKK_RECT_VERTEX_GLSL;
extern const char* __RKK_RECT_FRAGMENT_GLSL;

rkk_Renderer rkk_GetRenderer(rkk_vec2 ScreenSize);
void rkk_DestroyRenderer(rkk_Renderer *Rnd);
void rkk_Clear(rkk_Color Color);
void rkk_RendererDrawShape(float *Vertices, rkk_u32 *Indices, GLuint ShaderProgram, rkk_Uniform *Uniforms, rkk_u16 UniformsCount);
void rkk_RendererDrawRect(rkk_Renderer *Rnd, rkk_vec2 Position, rkk_vec2 Size, rkk_Color Color);

void __rkk_ApplyUnform(GLuint ShaderProgram, rkk_Uniform *Uinforms, rkk_u16 UniformsCout);

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

void rkk_RendererDrawShape(float *Vertices, rkk_u32 *Indices, GLuint ShaderProgram, rkk_Uniform *Uniforms, rkk_u16 UniformsCount) {
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glUseProgram(ShaderProgram);

    __rkk_ApplyUnform(ShaderProgram, Uniforms, UniformsCount);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

void __rkk_ApplyUnform(GLuint ShaderProgram, rkk_Uniform *Uniforms, rkk_u16 UniformsCout) {
    for(rkk_u16 i=0; i < UniformsCout; ++i) {
        GLuint loc = glGetUniformLocation(ShaderProgram, Uniforms[i].Name);

        if(loc == 0) {printf("RIKKA_CORE: Can't Find Uniform Named -> %s\n",  Uniforms[i].Name);continue;}

        if     (Uniforms[i].UniformType == rkkut_1i) glUniform1i(loc, (int) Uniforms[i].Values[0]); 
        else if(Uniforms[i].UniformType == rkkut_2i) glUniform2i(loc, (int) Uniforms[i].Values[0], (int) Uniforms[i].Values[1]); 
        else if(Uniforms[i].UniformType == rkkut_3i) glUniform3i(loc, (int) Uniforms[i].Values[0], (int) Uniforms[i].Values[1], (int) Uniforms[i].Values[2]); 
        else if(Uniforms[i].UniformType == rkkut_4i) glUniform4i(loc, (int) Uniforms[i].Values[0], (int) Uniforms[i].Values[1], (int) Uniforms[i].Values[2], (int) Uniforms[i].Values[3]); 
        else if(Uniforms[i].UniformType == rkkut_1f) glUniform1f(loc, Uniforms[i].Values[0]); 
        else if(Uniforms[i].UniformType == rkkut_2f) glUniform2f(loc, Uniforms[i].Values[0], Uniforms[i].Values[1]); 
        else if(Uniforms[i].UniformType == rkkut_3f) glUniform3f(loc, Uniforms[i].Values[0], Uniforms[i].Values[1], Uniforms[i].Values[2]); 
        else if(Uniforms[i].UniformType == rkkut_4f) glUniform4f(loc, Uniforms[i].Values[0], Uniforms[i].Values[1], Uniforms[i].Values[2], Uniforms[i].Values[3]); 
    }
}
