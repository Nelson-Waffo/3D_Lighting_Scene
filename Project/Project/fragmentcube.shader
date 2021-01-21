// a basic fragment shader: it is called for every pixel (fragment) within the primitive

#version 330 core

// vector position of the fragment
in vec3 fragPos;
// normal vector for the fragment
in vec3 normal;
// texture coordinates
in vec2 texCoords;
// create a sample2D object to get the texture from the cpu
// uniform sampler2D grass;
// output colour of one fragment
out vec4 fragmentColour;

/* lighting maps and attenuation over the distance*/
// the idea here is that every fragment in the primitive should have its own individual diffuse and specular component based on 
// its colour
// light components
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // elements for the flashlight
    vec3 direction; // camera front
    float cutoff; // inner cutoff angle: spot light radius. radius of what will be lit.
    float outercutoff; // outer cutoff angle
    

    // attenuation values
    float constant;
    float lineare;
    float quadratic;
};
// material components
struct Material {
    // in this case, diffuse and ambient component are the same
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;
#define number 3
uniform Light lights[number];
// camera position
uniform vec3 cameraPos;
/*function prototype*/
vec3 calculateColor(Light light, vec3 normal, vec3 viewDirection);
// set to 0 for the flashlight to appear
uniform int flashlight;
/*end of function prototype*/

void main()
{ 
    // normalise the normal vector
    vec3 normal_vector = normalize(normal);
    //1) viewing direction
    vec3 viewDirection = normalize(cameraPos - fragPos);
    // calculate the final colour
    vec3 result;
    for (int i = 0; i < number - flashlight; ++i) // int i = 2; i < number; ++i : display only the flash light
    {
        result += calculateColor(lights[i], normal_vector, viewDirection);
    }
    fragmentColour = vec4(result, 1.0);
}

// a method to calculate the light colour for a given light and for one fragment
vec3 calculateColor(Light light, vec3 normal, vec3 viewDirection)
{
    // ambient component of the fragment colour
    vec3 ambient_component = light.ambient * vec3(texture(material.diffuse, texCoords));
    // diffuse component
    vec3 lightDirection = normalize(light.position - fragPos);
    float diffuseFactor = max(dot(lightDirection, normal), 0.0);
    vec3 diffuse_component = diffuseFactor * light.diffuse * vec3(texture(material.diffuse, texCoords));
    // specular component
    // reflection
    vec3 reflection = reflect(-lightDirection, normal);
    // specular factor
    float spec = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
    // specular component
    vec3 specular_component = spec * light.specular * vec3(texture(material.specular, texCoords));

    // flash light calculation
    if (light.position == cameraPos) {
        // the theta value: the angle between the light direction and the spotlight direction
        float theta = dot(lightDirection, normalize(-light.direction));
        // difference between the inner and outer cutoff angles
        float upsilon = light.cutoff - light.outercutoff;
        // intensity value indicating whether or not a fragment should be lit: when its higher than 0
        // the value gets clamped between 0 and 1
        float intensity = clamp((theta - light.outercutoff) / upsilon, 0.0, 1.0);
        // adapt it to the diffuse and specular components
        diffuse_component *= intensity;
        specular_component *= intensity;
    }

    // apply attenuation to the components
    // calculate attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.lineare * distance + light.quadratic * distance * distance);
    // attenuation = 1;
    /* end of lighting map */
    return ( attenuation * (ambient_component + diffuse_component + specular_component));
}