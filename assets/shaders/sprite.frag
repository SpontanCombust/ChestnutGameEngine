#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D uTextureUnit;

void main()
{
    FragColor = texture( uTextureUnit, texCoord );
}
