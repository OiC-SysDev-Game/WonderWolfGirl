#version 450 core


// in
in vec4 color;

// out
out vec4 frag_color;


void main(){
    frag_color = vec4(color);
}