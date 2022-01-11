R"(
#version 330 core 
out vec4 FragColor; 
uniform sampler2D uTexture;
uniform sampler2D uScreenTexture;
uniform vec2 uTexelSize;
uniform vec3 uOutlineColor;
in vec2 vUV;
void main() 
{ 
	vec4 screenTex = texture(uScreenTexture, vUV);
	float s0 = texture(uTexture, vUV).r;	
	float s1 = texture(uTexture, vUV + vec2(1,1) * uTexelSize).r;	
	float s2 = texture(uTexture, vUV + vec2(1,0) * uTexelSize).r;	
	float s3 = texture(uTexture, vUV + vec2(1,-1) * uTexelSize).r;	
	float s4 = texture(uTexture, vUV + vec2(0,-1) * uTexelSize).r;	
	float s5 = texture(uTexture, vUV + vec2(-1,-1) * uTexelSize).r;	
	float s7 = texture(uTexture, vUV + vec2(-1,1) * uTexelSize).r;	
	float s6 = texture(uTexture, vUV + vec2(-1,0) * uTexelSize).r;	
	float s8 = texture(uTexture, vUV + vec2(0,1) * uTexelSize).r;	
	float s = s0 + s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8;	
	float r = 0;
	if(s < 5 && s > 0) {r = 1;}
	vec3 outlineColor = uOutlineColor * r;
	FragColor = screenTex + vec4(outlineColor, 1.0);
} ;
)"