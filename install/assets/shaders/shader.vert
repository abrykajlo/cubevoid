#version 440 core

layout (location = 0) in vec3 vPosition;

void main()
{
    gl_Position.xyz = vPosition;
    gl_Position.w = 1.0;
}