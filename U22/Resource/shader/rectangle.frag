#version 450


// in
layout(location=0) in vec4 fragment_color;

// out
out vec4 out_color;


void main() {
	out_color = fragment_color;
}