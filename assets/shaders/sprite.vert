#version 330 core

in vec3 aPos;
in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat3 uTexClip;

void main()
{
    vec3 texCoordTransf = uTexClip * vec3( aTexCoord, 1.0 );
    texCoord = texCoordTransf.xy;
    
    gl_Position = uProjection * uView * uModel * vec4( aPos, 1.0 );
}