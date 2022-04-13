#version 330

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D shininess;
};

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOffInner;
    float cutOffOuter;
};

const int LIGHT_TYPE_DIRECTIONAL = 0;
const int LIGHT_TYPE_POINT = 1;
const int LIGHT_TYPE_SPOT = 2;

#define MAX_LIGHTS 8



in VS_OUT {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} fs_in;

uniform vec3 uCameraPosition;

uniform Material uMaterial;

uniform uint uLightCount;
uniform Light uLights[MAX_LIGHTS];
uniform int uLightTypes[MAX_LIGHTS];


out vec4 fs_out_color;



vec3 calcDirectionalLight(Light light, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse
    float diffuseImpact = max(dot(fs_in.normal, lightDir), 0.0);

    // specular and shininess
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);
    float shininess = texture(uMaterial.shininess, fs_in.uv).r;
    float specularImpact = pow(max(dot(viewDir, reflectDir), 0.0), shininess);


    // combine everything
    vec3 ambient = light.ambient * texture(uMaterial.diffuse, fs_in.uv).rgb;
    vec3 diffuse = light.diffuse * texture(uMaterial.diffuse, fs_in.uv).rgb * diffuseImpact;
    vec3 specular = light.specular * texture(uMaterial.specular, fs_in.uv).rgb * specularImpact;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(Light light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fs_in.pos);

    // diffuse
    float diffuseImpact = max(dot(fs_in.normal, lightDir), 0.0);

    // specular and shininess
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);
    float shininess = texture(uMaterial.shininess, fs_in.uv).r;
    float specularImpact = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // attenuation
    float dist = length(fs_in.pos - light.position);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);


    // combine everything
    vec3 ambient = light.ambient * texture(uMaterial.diffuse, fs_in.uv).rgb * attenuation;
    vec3 diffuse = light.diffuse * texture(uMaterial.diffuse, fs_in.uv).rgb * diffuseImpact * attenuation;
    vec3 specular = light.specular * texture(uMaterial.specular, fs_in.uv).rgb * specularImpact * attenuation;

    return ambient + diffuse + specular;
}

vec3 calcSpotLight(Light light, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fs_in.pos);

    // diffuse
    float diffuseImpact = max(dot(fs_in.normal, lightDir), 0.0);

    // specular and shininess
    vec3 reflectDir = reflect(-lightDir, fs_in.normal);
    float shininess = texture(uMaterial.shininess, fs_in.uv).r;
    float specularImpact = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // attenuation
    float dist = length(fs_in.pos - light.position);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // spotlight intensity
    float theta = dot(lightDir, normalize(light.direction));
    float epsilon = light.cutOffInner - light.cutOffOuter;
    float intensity = clamp((theta - light.cutOffOuter) / epsilon, 0.0, 1.0);


    // combine everything
    vec3 ambient = light.ambient * texture(uMaterial.diffuse, fs_in.uv).rgb * attenuation * intensity;
    vec3 diffuse = light.diffuse * texture(uMaterial.diffuse, fs_in.uv).rgb * diffuseImpact * attenuation * intensity;
    vec3 specular = light.specular * texture(uMaterial.specular, fs_in.uv).rgb * specularImpact * attenuation * intensity;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 viewDir = normalize(uCameraPosition - fs_in.pos);

    vec3 color = vec3(0.0);
    for(uint i = 0u; i < uLightCount; i++)
    {
        switch(uLightTypes[i])
        {
            case LIGHT_TYPE_DIRECTIONAL:
                color += calcDirectionalLight(uLights[i], viewDir);
                break;
            case LIGHT_TYPE_POINT:
                color += calcPointLight(uLights[i], viewDir);
                break;
            case LIGHT_TYPE_SPOT:
                color += calcSpotLight(uLights[i], viewDir);
                break;
        }
    }

    fs_out_color = vec4(color, 1.0);
}
