#version 330

in vec3 vert;
in vec3 color;

uniform mat4 MVP;

out vec3 vColor;

void main()
{
    gl_Position = MVP * vec4(vert, 1.0f);
    vColor = color;
}
