#version 330

in vec2 uv;
in vec3 color;

uniform sampler2D uTextureUnit;

out vec4 FragColor;

void main()
{
    float glyphAlpha = texture( uTextureUnit, uv ).r;

    FragColor = vec4( color, 1.0 ) * vec4( 1.0, 1.0, 1.0, glyphAlpha );
}