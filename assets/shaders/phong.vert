#version 330


in vec3 avPos;
in vec3 avNormal;
in vec2 avUV;

in vec3 aiTranslation;
in vec3 aiScale;
// no rotation for now

uniform mat4 uView;
uniform mat4 uProjection;


out VS_OUT {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vs_out;


void main()
{
    vec3 pos = avPos * aiScale + aiTranslation;
    gl_Position = uProjection * uView * vec4(pos, 1.0);

    vs_out.pos = pos;
    vs_out.normal = normalize(avNormal * vec3(1.0) / aiScale); // only scaling is involved so don't have to make an entire normal matrix
    vs_out.uv = avUV;
}
