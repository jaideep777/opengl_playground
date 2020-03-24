#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
out vec4 exCol;

uniform float pointSize=2;

void main(){
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_PointSize = pointSize;
   exCol = aCol;

}

