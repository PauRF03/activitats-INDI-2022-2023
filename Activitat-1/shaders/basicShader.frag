#version 330 core

out vec4 FragColor;
in vec4 fcolor;
uniform int dif;

void main() {
    if(dif == 0 || fcolor != vec4(0.f, 0.f ,0.5f, 1.f)){
        FragColor = fcolor;
    }else{
        if(mod(gl_FragCoord.x + gl_FragCoord.y, 64.f) > 32.f){
            FragColor = vec4(1, 0, 0, 1);
        }else{
            FragColor = vec4(1, 1, 1, 1);
        }
    }
}
