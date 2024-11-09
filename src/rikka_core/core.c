#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "../rikka_datatypes.h"

int rkk_InitGLFW();
int rkk_InitGLEW();
void rkk_TerminateGLFW();

GLFWwindow *rkk_GetWindow(rkk_u32 ResX, rkk_u32 ResY, const char* Title);
void rkk_DestroyWindow(GLFWwindow *Window);
void rkk_UseWindow(GLFWwindow *Window);
rkk_bool rkk_WindowShouldClose(rkk_Window *Window);

void rkk_SetVsync(rkk_bool State);

void rkk_PollEvents();
void rkk_SwapBuffers(rkk_Window *Window);

rkk_vec2 rkk_MakeVec2(float x, float y);
rkk_Color rkk_MakeColor(float Red, float Green, float Blue, float Alpha);
rkk_Color rkk_MakeColorU8(float Red, float Green, float Blue, float Alpha);

void GLAPIENTRY rkk_DebugCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

int rkk_SetDebug(rkk_bool State);

int rkk_InitGLFW() {
    int err = glfwInit();
    if (!err) printf("RIKKA_CORE: Failed To Initialize GLFW\nERROR: %i\n", err);
    return err;
}

int rkk_InitGLEW() {//TODO Add RIKKA_OK typedef
    int err = glewInit();
    if (err != GLEW_OK) printf("RIKKA_CORE: Failed To Initialize GLEW\nERROR: %i\n", err);
    return err;
}

void rkk_TerminateGLFW() {glfwTerminate();}

GLFWwindow *rkk_GetWindow(rkk_u32 ResX, rkk_u32 ResY, const char* Title) {
    GLFWwindow *Window = glfwCreateWindow(ResX, ResY, Title, NULL, NULL);
    if (!Window) printf("RIKKA_CORE: Failed To Create GlfwWindow!\n");
    return Window;
}

void rkk_DestroyWindow(GLFWwindow *Window) {glfwDestroyWindow(Window);}


void rkk_UseWindow(GLFWwindow *Window) {glfwMakeContextCurrent(Window);}
void rkk_SetVsync(rkk_bool State) {glfwSwapInterval((int) State);}

rkk_bool rkk_WindowShouldClose(rkk_Window *Window) {return (rkk_bool) glfwWindowShouldClose(Window);}

void rkk_PollEvents() {glfwPollEvents();}
void rkk_SwapBuffers(rkk_Window *Window) {glfwSwapBuffers(Window);}

rkk_vec2 rkk_MakeVec2(float x, float y) {return (rkk_vec2){x,y};}
rkk_Color rkk_MakeColor(float Red, float Green, float Blue, float Alpha) {return (rkk_Color){Red,Green,Blue,Alpha};}
rkk_Color rkk_MakeColorU8(float Red, float Green, float Blue, float Alpha) {
    rkk_Color Color = {
        Red   / 255.0f,
        Green / 255.0f,
        Blue  / 255.0f,
        Alpha / 255.0f
    };
    return Color;
}


void GLAPIENTRY rkk_DebugCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    const char* sourceStr = "";
    const char* typeStr = "";
    const char* severityStr = "";

    // Map the source enum to a string
    switch (source) {
        case GL_DEBUG_SOURCE_API: sourceStr = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: sourceStr = "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY: sourceStr = "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION: sourceStr = "Application"; break;
        case GL_DEBUG_SOURCE_OTHER: sourceStr = "Other"; break;
    }

    // Map the type enum to a string
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: typeStr = "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: typeStr = "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY: typeStr = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE: typeStr = "Performance"; break;
        case GL_DEBUG_TYPE_OTHER: typeStr = "Other"; break;
    }

    // Map the severity enum to a string
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: severityStr = "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM: severityStr = "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW: severityStr = "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Notification"; break;
    }

    // Print the debug message
    printf("OpenGL Debug Message:\n");
    printf("  Source: %s\n", sourceStr);
    printf("  Type: %s\n", typeStr);
    printf("  Severity: %s\n", severityStr);
    printf("  Message: %s\n", message);
}

int rkk_SetDebug(rkk_bool State) {
    if(State) {
        if (glewIsSupported("GL_ARB_debug_output")) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

            glDebugMessageCallback(rkk_DebugCallBack, NULL);
        } else {
            printf("OpenGL debug output not supported on this system.\n");
            return -1;
        }
    } else {
        glDisable(GL_DEBUG_OUTPUT);
        glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(NULL,NULL);
    }   
    return 0;
}
