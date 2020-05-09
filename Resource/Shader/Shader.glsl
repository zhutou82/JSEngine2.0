//type vertex
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

//type fragment
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
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float shinese;
};

struct Light
{
    vec3 pos;
    vec3 color;
    vec3 direction;

    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;

};

uniform Light directionalLight;
uniform Light ptLight;
uniform Material material;

uniform vec3 u_ObjectColor;
uniform vec3 u_CameraPos;


vec3 ComputeDirectionalLight(vec3 norm, Light light)
{
    vec3 ambient = light.color * light.ambient;


    vec3 lightDir   = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * light.color;

    vec3 viewDir = normalize(u_CameraPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shinese);
    vec3 specular = spec * light.specular * light.color;

    return (ambient + diffuse + specular) * material.color;
}


vec3 ComputePointLight(vec3 norm, Light light)
{
    vec3 ambient = light.color * light.ambient;

    
    vec3 lightVec = light.pos - v_FragPos;
    vec3 lightDir = normalize(lightVec);
    //vec3 distance = length(lightVec);


    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = diff * ptLight.color;

    vec3 viewDir = normalize(u_CameraPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shinese);
    vec3 specular = spec * light.specular * light.color;


    return (ambient + diffuse + specular) * material.color;
}

//
//vec3 CompuateSpotLight()
//{
//    
//
//}


void main()
{   
    vec3 norm = normalize(v_Normal);
    
    vec3 result = ComputeDirectionalLight(norm, directionalLight);
    result += ComputePointLight(norm, ptLight);

   
	fragcolor = vec4(result, 1.0);
	//fragcolor = texture(u_TextureID, v_TextCoor);
    //fragcolor = vec4(1,1,1,1);
}

//type
