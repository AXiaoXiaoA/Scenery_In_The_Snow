#version 330 core

out vec4 fColor;

in vec2 tTexture;
in vec3 tNormal;
in vec3 tFragPos;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;
uniform vec3 viewPos;

// 物体材质
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shiness;
};
uniform Material myMaterial;

// 平行光
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight myDirectionalLight;
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 环境光
    vec3 ambient  = light.ambient  * vec3(texture(myMaterial.diffuse, tTexture));
    // 漫反射
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(myMaterial.diffuse, tTexture));
    // 镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), myMaterial.shiness);
    vec3 specular = light.specular * spec * vec3(texture(myMaterial.specular, tTexture));
    // 将各个分量合并
    return (ambient + diffuse + specular);
}



void main() {
    // 根据法线方向决定使用哪个纹理
    vec4 firstTextureColor = texture(firstTexture, tTexture);
    vec4 secondTextureColor = texture(secondTexture, tTexture);
    vec3 lightDir = normalize(vec3(1.0, 1.0, -0.5));
    float diff = max(dot(tNormal, lightDir), 0.0);
    vec4 finalColor;
    if (tNormal.y > 0.9 || tNormal.y < -0.9) {
        finalColor = secondTextureColor;
    } else {
        finalColor = firstTextureColor;
    }

    // 平行光
    vec3 norm = normalize(tNormal);
    vec3 viewDir = normalize(viewPos - tFragPos);
    vec3 result = CalculateDirectionalLight(myDirectionalLight, norm, viewDir);

    fColor =  finalColor * vec4(result, 1.0);
}
