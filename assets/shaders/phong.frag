#version 330

in VS_OUT {
    vec3 normal;
    vec2 uv;
} fs_in;

uniform struct Material {
    sampler2D diffuse;
} uMaterial;


out vec4 color;

void main()
{
    color = texture(uMaterial.diffuse, fs_in.uv);
}
