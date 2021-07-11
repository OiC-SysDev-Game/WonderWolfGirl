#version 450


// in
layout(location=0) in vec3 vertex_position;
layout(location=1) in vec4 vertex_color;

// out
out vec4 fragment_color;

// uniform
uniform vec4 uniform_color;
uniform mat4 model_transform;
uniform mat4 view_projection;


void main() {
    vec4 pos = vec4(vertex_position, 1.0);
    gl_Position = view_projection * model_transform * pos;

	fragment_color = uniform_color;
}