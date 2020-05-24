//type vertex
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textCoor;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_ViewMat;
uniform mat4 u_ProjMat; 
uniform mat4 u_ModelMat;

void main()
{
    gl_Position = u_ProjMat * u_ViewMat * u_ModelMat * vec4(pos, 1.0);
    v_FragPos = vec3(u_ModelMat * vec4(pos, 1.0));
    v_TexCoord = textCoor; 
    v_Normal = mat3(transpose(inverse(u_ModelMat))) * normal; //better do that CPU side
}

//type fragment
#version 460 core
out vec4 fragcolor;

//in from other shaders
in vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal;

struct Material
{
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    //sampler2D diffuse;
    //sampler2D specular;

    float shininess;
};

struct Light
{
    vec3 pos;
    vec3 color;
    vec3 direction;

    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float innerCutOff;
    float outerCutOff;

};

uniform Light directionalLight;
uniform Light ptLight;
uniform Light spotLight;
uniform Material material;

uniform vec3 u_ObjectColor;
uniform vec3 u_CameraPos;


uniform sampler2D texture_diffuse0;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;

uniform sampler2D texture_specular0;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

uniform sampler2D u_DiffuseTexture; 
uniform int u_SpecularMapIndex;

//functions
vec3 ComputeDirectionLight(vec3 norm, Light directionalLight);
vec3 ComputePointLight(vec3 norm, Light ptLight);
vec3 ComputeSpotLight(vec3 norm, Light spLight);

//helper function
vec3 ComputeAmbient(vec3 lightAmbient)
{
    return lightAmbient * vec3(texture(u_DiffuseTexture, v_TexCoord)); // Dont keep sampling the same texture. sample once and pass in the value in the function.
    return lightAmbient * material.diffuse;
}

vec3 ComputeDiffuse(vec3 norm, vec3 LightDir, vec3 lightDiffuse)
{
    float diff = max(dot(norm, LightDir), 0);
    return lightDiffuse * (diff * vec3(texture(u_DiffuseTexture, v_TexCoord))); // Dont keep sampling the same texture. sample once and pass in the value in the function.
    return lightDiffuse * (diff * material.diffuse);
}

vec3 ComputeSpecular(vec3 norm, vec3 LightDir, vec3 lightSpecular)
{
    vec3 viewDir = normalize(u_CameraPos - v_FragPos);
    vec3 reflectDir = reflect(-LightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return lightSpecular * (spec * vec3(texture(texture_specular1, v_TexCoord)));
    return lightSpecular * (spec * material.specular);
}


vec3 ComputeDirectionLight(vec3 norm, Light directionalLight)
{
    vec3 lightDir   = normalize(-directionalLight.direction);

    vec3 ambient     = ComputeAmbient(directionalLight.ambient);
    vec3 diffuse     = ComputeDiffuse(norm, lightDir, directionalLight.diffuse);
    vec3 speculation  = ComputeSpecular(norm, lightDir, directionalLight.specular);

    return ambient + diffuse + speculation;
}

vec3 ComputePointLight(vec3 norm, Light ptLight)
{
    vec3 lightVec = ptLight.pos - v_FragPos;
    vec3 lightDir = normalize(lightVec);

    vec3 ambient = ComputeAmbient(ptLight.ambient);
    vec3 diffuse = ComputeDiffuse(norm, lightDir, ptLight.diffuse);
    vec3 speculation = ComputeSpecular(norm, lightDir, ptLight.specular);

    //attenuation
    float distance = length(lightVec);
    float attenuation = 1.0 / (ptLight.constant + ptLight.linear * distance + ptLight.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    speculation *= attenuation;

    return ambient + diffuse + speculation;

}

vec3 ComputeSpotLight(vec3 norm, Light spLight)
{
    vec3 lightVec = spLight.pos - v_FragPos;
    vec3 lightDir = normalize(lightVec);

    vec3 ambient = ComputeAmbient(spLight.ambient);
    vec3 diffuse = ComputeDiffuse(norm, lightDir, spLight.diffuse);
    vec3 speculation = ComputeSpecular(norm, lightDir, spLight.specular);

    float theTa = dot(normalize(-spLight.direction), lightDir);
    float epsilon = spLight.innerCutOff - spLight.outerCutOff;
    float intensity = clamp( (theTa - spLight.outerCutOff)/epsilon, 0.0, 1.0);

    diffuse *= intensity;
    speculation *= intensity;

    return ambient + diffuse + speculation;
}

void main()
{
    vec3 norm = normalize(v_Normal);
    
    //vec3 result = ComputeDirectionalLight(norm, directionalLight);
    //result += ComputePointLight(norm, ptLight);


    vec3 result = ComputeDirectionLight(norm, directionalLight);
    result += ComputePointLight(norm, ptLight);
    
    //vec3 spotLightVal = ComputeSpotLight(norm, spotLight);
    //result += spotLightVal;


    fragcolor = vec4(result, 1.0);
    fragcolor = texture(u_DiffuseTexture, v_TexCoord);
    //fragcolor = vec4(1,1,1,1);
}

//type
