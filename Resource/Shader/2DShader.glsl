//type vertex
#version 460 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec4 Color;
layout (location = 2) in vec2 TextCoord;
layout (location = 3) in float TextureID;

//out vec3 v_FragPos;
out vec4 v_Color;
out vec2 v_TextCoor;
out float v_TextureID;

uniform mat4 u_ViewProjMat;

void main()
{
    gl_Position = u_ViewProjMat * vec4(Pos, 1.0);
    v_TextCoor = TextCoord;
    v_Color = Color;
    v_TextureID = TextureID;
}
       
//type fragment
#version 460 core
out vec4 fragColor; 

//uniform
uniform sampler2D u_Textures[8];

//in from vertex shaders
in vec4 v_Color;
in vec2 v_TextCoor;
in float v_TextureID;

void main()
{
	//fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    fragColor = texture(u_Textures[int(v_TextureID)], v_TextCoor);
    fragColor = v_Color;
}

//type
