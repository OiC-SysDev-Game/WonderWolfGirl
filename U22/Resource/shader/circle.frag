#version 450


// in
layout(location=0) in vec4 fragment_color;
//in vec4 fragment_color;

// out
out vec4 out_color;


void main() {
	//out_color = vec4(1.0, 1.0, 0.0, 1.0);
	out_color = fragment_color;
}