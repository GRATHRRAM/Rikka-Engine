#include "rikka_core.h"
#include "rikka_datatypes.h"

int main(void) {
    if(!rkk_InitGLFW()) return -1;

    rkk_Window *Window = rkk_GetWindow(1200, 720, "Rikka Engine");

    if(!Window) {
        rkk_TerminateGLFW();
        return -2;
    }

    rkk_UseWindow(Window);

    while(!rkk_WindowShouldClose(Window)) {
        rkk_PoolEvents();
        rkk_Clear(0.47, 0.0,0.46, 1.0);
        rkk_SwapBuffers(Window);
    }

    return 0;
}
