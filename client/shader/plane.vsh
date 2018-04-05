#version 330 core
layout(location = 0) in vec3 model_space;

void main() {
    gl_Position.xyz = model_space;
    gl_Position.w = 1.0;
}
