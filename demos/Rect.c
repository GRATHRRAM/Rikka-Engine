#include "rikka_core.h"
#include "rikka_datatypes.h"
#include <stdio.h>

int main(void) {
    if(!rkk_InitGLFW()) return -1;
    rkk_Window *Window = rkk_GetWindow(800, 600, "Rikka Engine: Rect.c");
    if(!Window) {rkk_TerminateGLFW();return -2;}

    rkk_UseWindow(Window);
    if(rkk_InitGLEW() != GLEW_OK){rkk_TerminateGLFW();return -3;}

    rkk_SetVsync(rkk_enable);
    printf("OpenGL Version -> %s\n", glGetString(GL_VERSION));
    
    rkk_Renderer Renderer = rkk_GetRenderer(rkk_MakeVec2(800,600));

    while(!rkk_WindowShouldClose(Window)) {
        rkk_PollEvents();
        
        rkk_Clear(rkk_MakeColor(0,0,0,1));

        rkk_RndDrawRect(&Renderer,
            rkk_MakeVec2(50,50),
            rkk_MakeVec2(200,200),
            rkk_MakeColor(0.7,0,0,0.5)
        );
        
        rkk_RndDrawRect(&Renderer,
            rkk_MakeVec2(200,200),
            rkk_MakeVec2(200,200),
            rkk_MakeColor(0,0,0.7,0.5)
        );
        
        rkk_RndDrawRect(&Renderer,
            rkk_MakeVec2(500,300),
            rkk_MakeVec2(200,200),
            rkk_MakeColor(0,0.7,0,0.5)
        );

        rkk_SwapBuffers(Window);
    }

    rkk_DestroyRenderer(&Renderer);
    rkk_DestroyWindow(Window);
    rkk_TerminateGLFW();
    return 0;
}

/*float ndc_x = screen_x / width * 2 - 1;
float ndc_y = screen_y / height * 2 - 1;*/
