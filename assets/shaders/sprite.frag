#version 330 core

in vec2 uv;
in vec3 tint;
in float tintFactor;

out vec4 FragColor;

uniform sampler2D uTextureUnit;

void main()
{
    vec4 texel = texture( uTextureUnit, uv );
    FragColor = mix( texel, vec4( tint, texel.a ), tintFactor );
}
