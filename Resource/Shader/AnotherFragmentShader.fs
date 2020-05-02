#version 460 core
out vec4 fragcolor;

//uniform
uniform vec4 u_Color;
uniform sampler2D u_TextureID;

//in from other shaders
in vec2 v_TextCoor;
in vec3 v_FragPos;
in vec3 v_Normal;

uniform vec3 u_ObjectColor;

void main()
{
	fragcolor = vec4(u_ObjectColor, 1.0);
}

