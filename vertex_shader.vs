#version 330 core
layout (location = 0) in vec3 _pos;


void main()
{
	gl_Position = vec4(_pos.x, _pos.y, _pos.z 1.0);

}