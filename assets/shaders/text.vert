#version 330

in vec2 avPos;
in vec2 avUV;
in vec4 avColor;
in vec2 avTranslation;
in vec2 avScale;

uniform mat4 uProjection;
uniform mat4 uView;

out vec2 uv;
out vec4 color;


mat4 mat4Translation( vec2 t )
{
    return mat4(    
        1.0,        0.0,        0.0,        0.0,
        0.0,        1.0,        0.0,        0.0,
        0.0,        0.0,        1.0,        0.0,
        t.x,        t.y,        0.0,        1.0
    );
}

mat4 mat4Scale( vec2 s )
{
    return mat4(
        s.x,        0.0,        0.0,        0.0,
        0.0,        s.y,        0.0,        0.0,
        0.0,        0.0,        1.0,        0.0,
        0.0,        0.0,        0.0,        1.0
    );
}

mat4 makeModel()
{
    mat4 translation = mat4Translation( avTranslation );
    mat4 scale = mat4Scale( avScale );

    return translation * scale;
}

void main()
{
    mat4 model = makeModel();

    gl_Position = uProjection * uView * model * vec4( avPos, 0.0, 1.0 );
    uv = avUV;
    color = avColor;
}