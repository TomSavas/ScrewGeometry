#version 330
in vec4 color;
in vec2 scaled_uv;
in vec4 n;
in vec4 world_pos;
in vec2 viewport_pos;

out vec4 frag_color;

uniform sampler2D tex;
uniform bool fake_portal;

void main()
{
    //frag_color = texture(tex, vec2(gl_FragCoord.x / 800.0, gl_FragCoord.y / 600.0));

    frag_color = texture(tex, vec2(gl_FragCoord.x / 800.0, gl_FragCoord.y / 600.0));
    //frag_color = vec4(gl_ClipDistance[0], 0.0, 0.0, 1.0);

    //frag_color = texture(tex, scaled_uv);
    //frag_color = vec4(scaled_uv, 0.0, 1.0);
    //frag_color = vec4(gl_FragCoord.x / 800.0, gl_FragCoord.y / 600.0, 0.0, 1.0);
}