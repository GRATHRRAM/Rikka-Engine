#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>

GLuint rkk_CompileShader(const char* source, GLenum type);
GLuint rkk_CreateShaderProgram(const char* VertextShader, const char* FragmentShader);
void rkk_DeleteShaderProgram(GLuint ShaderProgram);

GLuint rkk_CompileShader(const char* source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("RIKKA_CORE: Shader compilation failed\n%s\n", infoLog);
    }

    return shader;
}

GLuint rkk_CreateShaderProgram(const char* VertextShader, const char* FragmentShader) {
    GLuint vertexShader = rkk_CompileShader(VertextShader, GL_VERTEX_SHADER);
    GLuint fragmentShader = rkk_CompileShader(FragmentShader, GL_FRAGMENT_SHADER);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("RIKKA_CORE: Program linking failed\n%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void rkk_DeleteShaderProgram(GLuint ShaderProgram) {
    glDeleteProgram(ShaderProgram);
}
