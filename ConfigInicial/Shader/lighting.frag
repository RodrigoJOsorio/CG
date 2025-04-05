#version 330 core

#define NUMBER_OF_POINT_LIGHTS 4

// Estructura del material: se incluyen dos texturas (diffuse y specular), un coeficiente de brillo y la componente emisiva
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    vec3 emissive; // Permite que el objeto se autoilumine
};

// Estructura para la luz direccional
struct DirLight {
    vec3 direction;    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Estructura para una luz puntual
struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Estructura para un spotlight
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Variables de entrada del vertex shader
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

// Salida final
out vec4 color;

// Uniformes globales
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform int transparency; // Control de transparencia (por ejemplo, para descartar fragmentos)

// Prototipos de funciones para calcular cada tipo de iluminación
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    // Normalización de la normal y cálculo del vector de vista
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Se calcula la iluminación de la luz direccional
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    
    // Se acumulan las contribuciones de cada luz puntual
    for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++) {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    
    // Se suma la contribución del spotlight
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    
    // Se añade la componente emisiva (autoiluminación), útil para los modelos sun y moon
    result += material.emissive;
    
    // Se multiplica el resultado final por el color obtenido de la textura difusa
    vec3 texColor = vec3(texture(material.diffuse, TexCoords));
    vec3 finalColor = texColor * result;
    color = vec4(finalColor, 1.0);
    
    // Si el canal alfa es muy bajo y la transparencia está habilitada, se descarta el fragmento
    if (color.a < 0.1 && transparency == 1)
        discard;
}

// Función para calcular la iluminación direccional
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    return ambient + diffuse + specular;
}

// Función para calcular la iluminación de una luz puntual
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ambient + diffuse + specular;
}

// Función para calcular la iluminación de un spotlight
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ambient + diffuse + specular;
}
