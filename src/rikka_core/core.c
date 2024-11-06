#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>

#include "../rikka_datetypes.h"

int rkk_InitGLFW();
int rkk_InitGLEW();
void rkk_TerminateGLFW();

GLFWwindow *rkk_GetWindow(rkk_u32 ResX, rkk_u32 ResY, const char* Title);
void rkk_DestroyWindow(GLFWwindow *Window);
void rkk_UseWindow(GLFWwindow *Window);

void rkk_SetVsync(rkk_bool State);

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
