#version 440 core

layout (location = 0) in vec2 vPosition;

void main()
{
    gl_Position.xy = vPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}