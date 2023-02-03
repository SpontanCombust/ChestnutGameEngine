#version 330 core

in vec2 avPos;
in vec4 avColor;

uniform mat4 uView;
uniform mat4 uProjection;

out vec4 frag;

void main()
{
    gl_Position = uProjection * uView * vec4( avPos, 0.0, 1.0 );
    frag = avColor;
}