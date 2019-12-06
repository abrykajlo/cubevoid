#version 440 core
//inputs
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
//outputs
out vec3 fNormal;
//uniforms
layout (location = 0) uniform mat4 MVP; 

void main()
{
    fNormal = vec3(1.0, 0, 0);
    gl_Position = MVP * vec4(vPosition, 1.0);
}