#version 330 core
in vec4 color;
in vec2 scaled_uv;
//in vec2 troll_uv;
in vec4 n;
in vec4 world_pos;

out vec4 frag_color;

uniform vec3 light_pos;
uniform vec3 camera_pos;

uniform sampler2D tex0;
//uniform sampler2D tex1;

void main() 
{
    vec3 lightDir = normalize(world_pos.xyz - light_pos);
    vec3 lightReflectionDir = reflect(lightDir, normalize(n.xyz));

    float ambientIntensity = 1.f;
    float diffuseIntensity = max(dot(normalize(n.xyz), normalize(light_pos - world_pos.xyz)), 0.0);
    float specularIntensity = pow(max(dot(lightReflectionDir, normalize(camera_pos - world_pos.xyz)), 0.0), 256);

    // Allow lighting from the backside 
    //if (diffuseIntensity < 0.f)
    //    diffuseIntensity *= -1.f;

    float intensity = ambientIntensity * 0.1f + diffuseIntensity * 0.7f + specularIntensity * 0.2f;

    frag_color = texture(tex0, scaled_uv) * intensity;
    //frag_color = vec4(vec3(intensity), 1.0);
    //frag_color = vec4(vec3(gl_FragCoord.z), 1.0);
    //frag_color = vec4(scaled_uv, 0.0, 1.0);
    //frag_color = world_pos;

    //frag_color = vec4(gl_ClipDistance[0], gl_ClipDistance[1], gl_ClipDistance[2], 1.0);
}
