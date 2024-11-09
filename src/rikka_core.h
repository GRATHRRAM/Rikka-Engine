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

rkk_vec2 rkk_MakeVec2(float x, float y);
rkk_Color rkk_MakeColor(float Red, float Green, float Blue, float Alpha);
rkk_Color rkk_MakeColorU8(float Red, float Green, float Blue, float Alpha);

void GLAPIENTRY rkk_DebugCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
int rkk_SetDebug(rkk_bool State);
//void rkk_error_callback(int error, const char* desc);

void rkk_PollEvents();
void rkk_SwapBuffers(rkk_Window *Window);

/* shaders.c */
GLuint rkk_CompileShader(const char* source, GLenum type);
GLuint rkk_CreateShaderProgram(const char* VertextShader, const char* FragmentShader);
void rkk_DeleteShaderProgram(GLuint ShaderProgram);

/* renderer.c */
rkk_Renderer rkk_GetRenderer();
void rkk_DestroyRenderer(rkk_Renderer *Rnd);
void rkk_Clear(rkk_Color Color);
void rkk_RndDrawRect(rkk_Renderer *Rnd, rkk_vec2 Position, rkk_vec2 Size, rkk_Color Color);

#endif
