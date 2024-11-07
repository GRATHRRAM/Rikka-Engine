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
        rkk_Clear(rkk_MakeColor(0.47f, 0.0f,0.46f, 1.0f));
        rkk_SwapBuffers(Window);
    }

    rkk_DestroyWindow(Window);
    rkk_TerminateGLFW();
    return 0;
}
