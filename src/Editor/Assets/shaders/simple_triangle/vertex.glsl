#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 uTransform;

out vec3 vPos;

void main()
{
   vPos = aPos;
   gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position /= gl_Position.w;
}