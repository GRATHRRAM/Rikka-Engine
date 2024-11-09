const char* __RKK_RECT_VERTEX_GLSL =
"#version 330 core\n"
"\n"
"layout(location = 0) in vec3 aPos;    // Vertex position\n"
"out vec4 fragColor;  // Output to fragment shader\n"
"\n"
"uniform vec4 rectColor; // Uniform color to apply to rectangle\n"
"\n"
"void main() {\n"
"   gl_Position = vec4(aPos, 1.0);  // Directly use the position in screen coordinates\n"
"   fragColor = rectColor;  // Pass the color to the fragment shader\n"
"}";

const char* __RKK_RECT_FRAGMENT_GLSL =
"#version 330 core\n"
"\n"
"in vec4 fragColor;  // Input from the vertex shader\n"
"out vec4 FragColor; // Final color to output\n"
"\n"
"void main() {\n"
"// Output the color directly\n"
"   FragColor = fragColor;\n"
"}";
