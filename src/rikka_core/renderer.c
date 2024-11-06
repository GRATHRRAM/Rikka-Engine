#include <GL/glew.h>
#include <GLFW/glfw3.h>

void rkk_Clear(float Red, float Green, float Blue, float Alpha);

void rkk_Clear(float Red, float Green, float Blue, float Alpha) {
    glClearColor(Red, Green, Blue, Alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}
