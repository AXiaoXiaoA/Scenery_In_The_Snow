#version 330 core

out vec4 fColor;

in vec2 tTexture;
in vec3 tNormal;
in vec3 tFragPos;

uniform vec3 viewPos;

// 物体材质
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shiness;
}; 
uniform Material material;

// 平行光
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight myDirectionalLight;
vec3 CalculateDirectionalLight(DirectionalLight light, Material mat, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 环境光
    vec3 ambient  = light.ambient  * vec3(texture(mat.texture_diffuse1, tTexture));
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(mat.texture_diffuse1, tTexture));
    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shiness);
    vec3 specular = light.specular * spec * vec3(texture(mat.texture_specular1, tTexture));
    // 将各个分量合并
    return (ambient + diffuse + specular);
}

void main()
{    
    vec3 norm = normalize(tNormal);
    vec3 viewDir = normalize(viewPos - tFragPos);

    vec3 result = CalculateDirectionalLight(myDirectionalLight, material, norm, viewDir);
        
    fColor = vec4(result, 1.0f);
}