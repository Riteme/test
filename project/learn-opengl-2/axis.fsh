#version 330 core

in vec3 outColor;

out vec4 finalColor;

void main(){
    finalColor = vec4(outColor, 1.0);
}
