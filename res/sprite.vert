#version 330
layout (location = 0) in vec2 posn;
void main()
{
	gl_Position = vec4(posn,0.0f,1.0f);
}