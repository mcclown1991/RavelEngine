#version 330 core

layout(location = 0) in vec3 vertices;
layout(location = 1) in vec2 uv;

out vec2 UV;

uniform mat4 world;
uniform mat4 projection;
uniform mat4 camera;

void main(){
	gl_Position = world * vec4(vertices, 1);
	gl_Position = projection * gl_Position;
	gl_Position = camera * gl_Position;

	UV = uv;
}