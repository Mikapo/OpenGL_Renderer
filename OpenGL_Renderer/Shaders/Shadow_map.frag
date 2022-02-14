#version 330 core


void main()
{             
    gl_FragDepth = gl_FragCoord.z;
    float bias = 0.0004;
    gl_FragDepth += gl_FrontFacing ? bias : 0.0f;
}