#version 330

in vec2 vert;
in vec3 color;

uniform mat4 MVP;

out vec3 vColor;

void main()
{
    gl_Position = MVP * vec4(vert, 0.0f, 1.0f);
    vColor = color;
}
