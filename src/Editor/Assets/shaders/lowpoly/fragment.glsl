#version 330 core
out vec4 FragColor;

in vec3 vPos;
in vec3 vNorm;
in float vLight;

uniform vec3 uLightColor;
uniform vec3 uAmbientColor;

void main()
{
   FragColor = vec4(1.0f, 0.0f, 0.8f, 1.0f);
   vec3 lightColor = mix(uAmbientColor, uLightColor, vLight);
   FragColor = vec4(lightColor, 1.0);
   //FragColor = vec4(vec3(vLight), 1.0);
}