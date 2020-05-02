#type vertex
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoor;

out vec2 v_TextCoor;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_ModelMat;
uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat; 
void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_ModelMat * vec4(pos, 1.0);
    v_FragPos = vec3(u_ModelMat * vec4(pos, 1.0));
    v_TextCoor = textCoor; 
    v_Normal = mat3(transpose(inverse(u_ModelMat))) * normal;
}

#type fragment
#version 460 core
out vec4 fragcolor;

//uniform
uniform vec4 u_Color;
uniform sampler2D u_TextureID;

//in from other shaders
in vec2 v_TextCoor;
in vec3 v_FragPos;
in vec3 v_Normal;

struct Material
{
    float ambient;
    float diffuse;
    float specular;

};

struct PointLight
{
    vec3 pos;
    vec3 color;

    float ambient;
    float diffuse;
    float specular;

};

uniform PointLight ptLight;
uniform Material material;

uniform vec3 u_ObjectColor;


void main()
{
    vec3 ambient = ptLight.color * ptLight.ambient;

    vec3 norm = normalize(v_Normal);
    //vec3 lightVec = ;
    vec3 lightDir = normalize(ptLight.pos - v_FragPos);

    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * ptLight.color;


    vec3 result = (ambient + diffuse) * u_ObjectColor;

	fragcolor = vec4(result, 1.0);
	//fragcolor = vec4(1.0, 1.0, 1.0, 1.0);
}

#type