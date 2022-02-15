#version 330 core


void main()
{             
    gl_FragDepth = gl_FragCoord.z;
    float bias = 1;
    gl_FragDepth += gl_FrontFacing ? bias : 0.0f;
}