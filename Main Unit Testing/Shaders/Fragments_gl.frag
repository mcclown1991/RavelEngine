#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D ObjSamplerState;

void main(){
	color = texture(ObjSamplerState, UV).rgb;
}