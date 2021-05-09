#version 330 core

in vec2 aPos;
in vec2 aUV;

out vec2 uv;

uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    uv = aUV;
    
    gl_Position = uProjection * uView * vec4( aPos, 0.0, 1.0 );
}