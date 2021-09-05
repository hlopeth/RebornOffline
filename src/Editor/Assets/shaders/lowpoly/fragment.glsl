#version 330 core
layout (location = 0) out vec3 FragColor;
layout (location = 1) out vec3 outline;

in vec3 vPos;
in vec3 vNorm;
in float vLight;

uniform vec3 uLightColor;
uniform vec3 uAmbientColor;
uniform float uOutlined;

void main()
{
   FragColor = vec3(1.0f, 0.0f, 0.8f);
   vec3 lightColor = mix(uAmbientColor, uLightColor, vLight);
   FragColor = vec3(lightColor);
   outline = step(0.5, uOutlined) * vec3(1.0, 0.0, 0.0);
}