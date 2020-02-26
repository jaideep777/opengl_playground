#version 330 core

in vec4 exCol;
in vec2 exUV;

out vec4 FragColor;

uniform sampler2D tex;

void main(){
   FragColor = texture(tex, ex_UV)
   // FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);

}


