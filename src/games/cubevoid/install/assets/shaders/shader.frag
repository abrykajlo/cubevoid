#version 440 core
//inputs
in vec3 fNormal;
//outputs
out vec4 fColor;
//uniforms
layout (location = 1) uniform vec3 eye; 

void main()
{
    fColor = vec4(gl_FragCoord.zzz, 1.0);
}