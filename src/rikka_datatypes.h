#ifndef RIKKA_DATATYPES
#define RIKKA_DATATYPES

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define rkk_enable  1
#define rkk_disable 0
#define rkk_true  1
#define rkk_false 0

typedef unsigned char rkk_bool;

typedef unsigned long long int rkk_u64;
typedef unsigned int   rkk_u32;
typedef unsigned short rkk_u16;
typedef unsigned char  rkk_u8;

typedef GLFWwindow rkk_Window;

typedef struct rkk_vec2 {
    float x;
    float y;
} rkk_vec2;

typedef struct rkk_U8Color {
    rkk_u8 r;
    rkk_u8 g;
    rkk_u8 b;
    rkk_u8 a;
} rkk_U8Color;

typedef struct rkk_Color {
    float r;
    float g;
    float b;
    float a;
} rkk_Color;

typedef struct rkk_Renderer {
    rkk_vec2 ScreenSize;
    GLuint RectShader;
} rkk_Renderer;

typedef struct rkk_Uniform {
    char *Name;
    float Values[4];
    rkk_u8 UniformType;
} rkk_Uniform;

enum _rkk_unform_types {
    rkkut_1i,
    rkkut_2i,
    rkkut_3i,
    rkkut_4i,
    rkkut_1f,
    rkkut_2f,
    rkkut_3f,
    rkkut_4f
};

#endif //RIKKA_DATATYPES_H
