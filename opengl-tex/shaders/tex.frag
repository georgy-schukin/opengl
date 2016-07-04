#version 330

in vec2 worldVert;

out vec4 fragColor;

uniform sampler1D colorTex;

float func(vec2 coord) {
    return coord.x*sin(coord.x*25)*cos(coord.y*25);
    //return coord.x;
}

void main()
{    
    fragColor = texture(colorTex, func(worldVert));
}
