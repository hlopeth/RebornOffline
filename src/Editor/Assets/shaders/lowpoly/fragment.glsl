#version 330 core
out vec4 FragColor;

in vec3 vPos;
in vec3 vNorm;

uniform vec3 uLightColor;
uniform vec3 uAmbientColor;

void main()
{
   FragColor = vec4(1.0f, 0.0f, 0.8f, 1.0f);
   float light = clamp(dot(vNorm, vec3(0.0, 1.0, 0.0)), 0.0, 1.0);
   vec3 lightColor = light * uLightColor + uAmbientColor;
   FragColor = vec4(lightColor, 1.0);
}