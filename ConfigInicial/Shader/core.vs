#version 330 core
layout (location = 0) in vec3 position;


out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;
uniform vec3 color;

void main()
{
    gl_Position =projection*view*model*vec4(position, 1.0f);
    ourColor = color;
}