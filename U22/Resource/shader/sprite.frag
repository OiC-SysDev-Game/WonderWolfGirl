#version 450


// in
layout(location=0) in vec2 fragment_texcoord;

// out
out vec4 out_color;

// uniform
uniform vec4 uniform_color;
uniform sampler2D texture_sampler;


void main() {
	out_color = texture(texture_sampler, fragment_texcoord) * uniform_color;
}