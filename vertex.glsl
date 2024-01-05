#version 330 core

in vec3 vPosInput;
in vec3 vColorInput;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vColor;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosInput, 1.0f);
    vColor = vColorInput;
}
