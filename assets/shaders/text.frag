#version 330

in vec2 uv;
in vec4 color;

uniform sampler2D uTextureUnit;

out vec4 FragColor;

void main()
{
    float glyphAlpha = texture( uTextureUnit, uv ).r;

    FragColor = color * vec4( 1.0, 1.0, 1.0, glyphAlpha );
}