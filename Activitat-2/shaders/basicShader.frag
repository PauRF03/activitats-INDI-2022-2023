#version 330 core

in vec3 fcolor;
out vec4 FragColor;
uniform int Alternatiu;

void main() {
	if(Alternatiu == 1) FragColor = vec4(fcolor * vec3(1, 0 ,0), 1);
	else FragColor = vec4(fcolor, 1);
}
