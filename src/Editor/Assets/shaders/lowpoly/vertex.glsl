#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 uTransform;
uniform mat4 uNormalTransform;

out vec3 vPos;
out vec3 vNorm;

void main()
{
   vPos = aPos;
   vNorm = mat3(uNormalTransform) * aNorm;
   gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}