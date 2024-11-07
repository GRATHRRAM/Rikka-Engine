#include "rikka_core.h"
#include "rikka_datatypes.h"

int main(void) {
    if(!rkk_InitGLFW()) return -1;

    rkk_Window *Window = rkk_GetWindow(1200, 720, "Rikka Engine: Rect.c");

    if(!Window) {rkk_TerminateGLFW();return -2;}
    
    rkk_UseWindow(Window);
    
    if(rkk_InitGLEW() != GLEW_OK) {rkk_TerminateGLFW();return -3;}

    rkk_Renderer Renderer = rkk_GetRenderer();

    while(!rkk_WindowShouldClose(Window)) {
        rkk_PoolEvents();
        
        rkk_Clear(rkk_MakeColor(0,0,0,0.5));
        rkk_RndDrawRect(&Renderer,
            rkk_MakeVec2(100,100),
            rkk_MakeVec2(100,100),
            rkk_MakeColor(0.4f,0.4f,0.4f,1.0f)
        );

        rkk_SwapBuffers(Window);
    }

    rkk_DestroyRenderer(&Renderer);
    rkk_DestroyWindow(Window);
    rkk_TerminateGLFW();
    return 0;
}
