#version 330

in vec2 vert;

out vec2 worldVert;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vert, 0.0f, 1.0f);
    worldVert = vert;
}
