#version 440 core

layout (location = 0) out vec4 fColor;

void main()
{
    float z = gl_FragCoord.z;
    fColor = vec4(1.0-z, 1.0-z, 1.0-z, 1.0);
}