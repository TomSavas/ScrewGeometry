#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 color;
out vec2 scaled_uv;
//out vec2 troll_uv;
out vec4 n;
out vec4 world_pos;
out vec2 viewport_pos;

uniform float time;
uniform float spin_speed;

uniform vec3 light_pos;
uniform mat4 mvp;
uniform mat4 model;
uniform mat4 model_inverse_transpose;

uniform vec2 tex_scale;

float normalized_sin(float x)
{
    return (sin(x) * 0.5) + 0.5;
}

void main()
{
    float t = time * spin_speed; 

    gl_Position = mvp * vec4(pos.xyz, 1.0);
    world_pos = model * vec4(pos.xyz, 1.0);

    vec3 ndc = gl_Position.xyz / gl_Position.w;
    viewport_pos = ndc.xy * 0.5 + 0.5;

    color = vec4(pos.xyz, 1.0);

    scaled_uv = uv * tex_scale;

    //troll_uv.x = uv.x * cos(t) - uv.y * sin(t) - 
    //    0.5 * cos(t) + 0.5 * sin(t) + 0.5;
    //troll_uv.y = uv.x * sin(t) + uv.y * cos(t) -
    //    0.5 * cos(t) - 0.5 * sin(t) + 0.5;

    n = model_inverse_transpose * vec4(normal.xyz, 1.0);
}
