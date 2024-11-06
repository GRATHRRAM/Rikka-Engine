#ifndef RIKKA_CORE
#define RIKKA_CORE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <stdint.h>
#include <stdio.h>

#include "rikka_datetypes.h"

/* core.c */
int rkk_InitGLFW();
int rkk_InitGLEW();
void rkk_TerminateGLFW();

GLFWwindow *rkk_GetWindow(rkk_u32 ResX, rkk_u32 ResY, const char* Title);
void rkk_DestroyWindow(GLFWwindow *Window);
void rkk_UseWindow(GLFWwindow *Window);

void rkk_SetVsync(rkk_bool State);

void rkk_error_callback(int error, const char* desc);

/* shaders.c */
GLuint rkk_CompileShader(const char* source, GLenum type);
GLuint rkk_CreateShaderProgram(const char* VertextShader, const char* FragmentShader);
void rkk_DeleteShaderProgram(GLuint ShaderProgram);

#endif
