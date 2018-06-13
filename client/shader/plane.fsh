#version 330 core
out vec3 color;
in vec3 frag_color;
void main() {
   color = frag_color;
}
