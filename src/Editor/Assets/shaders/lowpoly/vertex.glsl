#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 uTransform;
uniform mat4 uModel;

out vec3 vPos;
out vec3 vNorm;
out float vLight;

void main()
{
   vPos = aPos;
   vNorm = transpose(inverse(mat3(uModel))) * aNorm;
   vNorm = normalize(vNorm);
   vLight = dot(vNorm, vec3(0.0, 1.0, 0.0)) + 1.0 * 0.5;
   //vNorm = aNorm;
   gl_Position = uTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}