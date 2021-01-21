#version 330 core

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;


struct Light {
    vec3 position;
    vec3 colour;
    // elements for the flashlight
    vec3 direction; // camera front
    float cutoff; 
    float outercutoff; 

    float constant;
    float lineare;
    float quadratic;
};

// 2 light sources: one light source and the flash light
#define number 2
uniform Light lights[number];

// camera position
uniform vec3 cameraPos;
// shine
float shininess = 32.0f;

out vec4 fragColour;

uniform sampler2D texture_diffuse1;

// set it to 0 for the flashlight to appear
uniform int flashlight;

/*forward declaration*/
vec3 calculateLight(Light light, vec3 normal, vec3 viewingDirection);
/**/

void main()
{
    // normalise the normal vector
    vec3 normal_vector = normalize(normal);
    // calculate the viewing direction on the fragment
    vec3 viewingDirection = normalize(cameraPos - fragPos);
    vec3 resultingColour;
    for (int i = 0; i < number - flashlight; ++i) {
        resultingColour += calculateLight(lights[i], normal_vector, viewingDirection);
    }

    fragColour = texture(texture_diffuse1, texCoords) * vec4(resultingColour, 1.0);
}

// a function to calculate light
vec3 calculateLight(Light light, vec3 normal, vec3 viewingDirection)
{
    //1) ambient light
    float ambientFactor = 0.2f;
    vec3 ambient = ambientFactor * light.colour;
    //2) diffuse light
    // light direction
    vec3 lightDirection = normalize(light.position - fragPos);
    float diffuseFactor = max(dot(lightDirection, normal), 0.0);
    vec3 diffuse = diffuseFactor * light.colour;
    //3) specular component
    // calculate the reflection
    vec3 reflection = reflect(-lightDirection, normal);
    // calculate the specular component
    float specularStrength = 0.9f;
    float spec = pow(max(dot(reflection, viewingDirection), 0.0), shininess);
    vec3 specular = specularStrength * spec * light.colour;
    // calculate the flashlight
        // flash light calculation
    if (light.position == cameraPos) {
        // the theta value: the angle between the light direction and the spotlight direction
        float theta = dot(lightDirection, normalize(-light.direction));
        // difference between the inner and outer cutoff angles
        float upsilon = light.cutoff - light.outercutoff;
        // intensity value indicating whether or not a fragment should be lit: when its higher than 1
        // the value gets clamped between 0 and 1
        float intensity = clamp((theta - light.outercutoff) / upsilon, 0.0, 1.0);
        // adapt it to the diffuse and specular components
        diffuse *= intensity;
        specular *= intensity;
    }

    // apply attenuation to the components
    // calculate attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.lineare * distance + light.quadratic * distance * distance);

    return (attenuation * (ambient + diffuse + specular));
}