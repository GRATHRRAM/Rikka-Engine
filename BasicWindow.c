#include "src/rikka_core.h"
#include "src/rikka_datetypes.h"

int main(void) {
    if(!rkk_InitGLFW()) return -1;

    rkk_Window *Window = rkk_GetWindow(1200, 720, "Rikka Engine");

    if(!Window) {
        rkk_TerminateGLFW();
        return -2;
    }

    while(!rkk_WindowShouldClose(Window)) {
        glfwPollEvents();

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Set the background color
        glClear(GL_COLOR_BUFFER_BIT);            // Clear the screen

        // Swap buffers
        glfwSwapBuffers(Window);
    }

    return 0;
}
