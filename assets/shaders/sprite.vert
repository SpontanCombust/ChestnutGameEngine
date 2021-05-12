#version 330 core

in vec2 avPos;
in vec2 avUVPos;

uniform vec2 uTexSize;

in vec2 aiTransl;
in vec2 aiScale;
in float aiRot;
in vec4 aiClipRect; // x, y, w, h in pixels

uniform mat4 uView;
uniform mat4 uProjection;

out vec2 uv;

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
    //                    rect.w, rect.h
    mat4 dim = mat4Scale( aiClipRect.zw );

    mat4 scale = mat4Scale( aiScale );
    
    mat4 rotation = mat4Rotation( aiRot );

    mat4 translation = mat4Translation( aiTransl );

    return translation * rotation * scale * dim;
}

mat4 makeClipping()
{
    //                              rect.w / tex.w                  rect.h / tex.h
    mat4 scale = mat4Scale( vec2( aiClipRect.z / uTexSize.x, aiClipRect.w / uTexSize.y ) );
    //                                              rect.x / tex.w              rect.y / tex.h
    mat4 translation = mat4Translation( vec2( aiClipRect.x / uTexSize.x, aiClipRect.y / uTexSize.y ) );

    return translation * scale;
}

void main()
{
    vec4 uvTransf = makeClipping() * vec4( avUVPos, 0.0, 1.0 );

    gl_Position = uProjection * uView * makeModel() * vec4( avPos, 0.0, 1.0 );
    uv = uvTransf.xy;
}