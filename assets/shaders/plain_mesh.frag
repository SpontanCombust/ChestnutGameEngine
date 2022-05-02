#version 330

in VS_OUT {
    vec2 uv;
} fs_in;

uniform struct Material {
    sampler2D diffuse;
} uMaterial;


out vec4 fs_out_color;


void main()
{
    fs_out_color = texture(uMaterial.diffuse, fs_in.uv);
}
