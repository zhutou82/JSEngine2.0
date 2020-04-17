#version 460 core
out vec4 fragcolor;
uniform vec4 u_Color;
in vec4 v_Color;

void main()
{
	fragcolor = v_Color;
}