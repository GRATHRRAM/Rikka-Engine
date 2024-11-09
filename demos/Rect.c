#include "rikka_core.h"
#include "rikka_datatypes.h"
#include <stdio.h>

int main(void) {
    if(!rkk_InitGLFW()) return -1;
    rkk_Window *Window = rkk_GetWindow(1200, 720, "Rikka Engine: Rect.c");
    if(!Window) {rkk_TerminateGLFW();return -2;}

    rkk_UseWindow(Window);
    if(rkk_InitGLEW() != GLEW_OK){rkk_TerminateGLFW();return -3;}

    rkk_SetVsync(rkk_enable);
    printf("OpenGL Version -> %s\n", glGetString(GL_VERSION));
    
    rkk_Renderer Renderer = rkk_GetRenderer();

    while(!rkk_WindowShouldClose(Window)) {
        rkk_PollEvents();
        
        rkk_Clear(rkk_MakeColor(0,0,0,1));

        rkk_RndDrawRect(&Renderer,
            rkk_MakeVec2(100,100),
            rkk_MakeVec2(100,100),
            rkk_MakeColor(1,1,1,1)
        );

        rkk_SwapBuffers(Window);
    }

    rkk_DestroyRenderer(&Renderer);
    rkk_DestroyWindow(Window);
    rkk_TerminateGLFW();
    return 0;
}
