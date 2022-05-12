#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitude = 0.04;
const float frequency = 4.0;
const float PI = 3.14159;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
  float distance = length(aPos);
  float effect = sin(amplitude*distance+time);
  gl_Position = projection*view*model*vec4(aPos.x,aPos.y+effect, aPos.z,1);
  TexCoords=vec2(aTexCoords.x,aTexCoords.y);

}