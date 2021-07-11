#version 450 core


// in
layout(location = 0) in vec3 vertex_position;

// out
out vec4 color;

// uniform
uniform mat4 model_transform;
uniform mat4 view_projection;


void main() {
    vec4 pos = vec4(vertex_position, 1.0);
    gl_Position = view_projection * model_transform * pos;

	color = vec4(1.0, 1.0, 1.0, 1.0f);
}