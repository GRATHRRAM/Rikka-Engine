#ifndef RIKKA_CORE
#define RIKKA_CORE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "rikka_datatypes.h"

/* core.c */
int rkk_InitGLFW();
int rkk_InitGLEW();
void rkk_TerminateGLFW();

GLFWwindow *rkk_GetWindow(rkk_u32 ResX, rkk_u32 ResY, const char* Title);
void rkk_DestroyWindow(rkk_Window *Window);
void rkk_UseWindow(rkk_Window *Window);
rkk_bool rkk_WindowShouldClose(rkk_Window *Window);

void rkk_SetVsync(rkk_bool State);

void rkk_error_callback(int error, const char* desc);

/* shaders.c */
GLuint rkk_CompileShader(const char* source, GLenum type);
GLuint rkk_CreateShaderProgram(const char* VertextShader, const char* FragmentShader);
void rkk_DeleteShaderProgram(GLuint ShaderProgram);

#endif
