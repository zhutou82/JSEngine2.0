//type vertex
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoor;

uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat; 
uniform mat4 u_ModelMat;

void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_ModelMat * vec4(pos, 1.0);
}
       
//type fragment
#version 460 core
out vec4 fragcolor;

void main()
{
	fragcolor = vec4(1.0, 1.0, 1.0, 1.0);
}

//type
