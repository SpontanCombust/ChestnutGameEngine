#version 330 core

in vec2 avPos;
in vec4 avColor;
in vec2 avOrigin;
in vec2 avTransl;
in vec2 avScale;
in float avRot;

uniform mat4 uView;
uniform mat4 uProjection;

out vec4 frag;

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
        0.0,        s.y,         0.0,        0.0,
        0.0,        0.0,        1.0,        0.0,
        0.0,        0.0,        0.0,        1.0
    );
}

mat4 mat4Rotation( float angle )
{
    float sine = sin(angle);
    float cosine = cos(angle);

    return mat4(
        cosine,     sine,       0.0,        0.0,
       -sine,       cosine,     0.0,        0.0,
        0.0,        0.0,        1.0,        0.0,
        0.0,        0.0,        0.0,        1.0
    );
}

mat4 makeModel()
{
    mat4 origin = mat4Translation( -avOrigin );
    
    mat4 scale = mat4Scale( avScale );
    
    mat4 rotation = mat4Rotation( avRot );

    mat4 translation = mat4Translation( avTransl );

    return translation * rotation * scale * origin;
}

void main()
{
    gl_Position = uProjection * uView * makeModel() * vec4( avPos, 0.0, 1.0 );
    frag = avColor;
}