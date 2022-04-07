#version 330

in VS_OUT {
    vec3 normal;
    vec2 uv;
} fs_in;

uniform struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
} uMaterial;


out vec4 color;

void main()
{
    color = texture(uMaterial.diffuse, fs_in.uv);
}
