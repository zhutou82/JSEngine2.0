#version 460 core
layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 color;

out vec4 v_Color;
void main()
{
    gl_Position = pos;
	v_Color = color;
}
       