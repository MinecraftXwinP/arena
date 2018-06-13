#version 330 core
layout(location = 0) in vec3 model_space;
layout(location = 1) in vec3 vertex_color;
out vec3 frag_color;
uniform mat4 mvp;

void main() {
    frag_color = vertex_color;
    gl_Position = mvp * vec4(model_space,1);
}
