#version 450


// in
layout(location=0) in vec3 vertex_position;
layout(location=1) in vec2 vertex_texcoord;

// out
layout(location=0) out vec2 fragment_texcoord;

// uniform
uniform vec2 uniform_size;
uniform vec4 uniform_rectangle; // left top right bottom
uniform mat4 model_transform;
uniform mat4 view_projection;

void Swap(inout float a, inout float b){
    float temp = a;
    a = b;
    b = temp;
}

vec2 ConputeTexcoordLeftTop(void) {
    float left = uniform_rectangle.x / uniform_size.x;
    float right = uniform_rectangle.z / uniform_size.x;
    float top = uniform_rectangle.y / uniform_size.y;
    float bottom = uniform_rectangle.w / uniform_size.y;

    if(left > right) {
        Swap(left, right);
    } // if
    if(top > bottom) {
        Swap(top, bottom);
    } // if
    
    return vec2(left, top);
}

vec2 ConputeTexcoordLeftBottom(void) {
    float left = uniform_rectangle.x / uniform_size.x;
    float right = uniform_rectangle.z / uniform_size.x;
    float top = uniform_rectangle.y / uniform_size.y;
    float bottom = uniform_rectangle.w / uniform_size.y;

    if(left > right) {
        Swap(left, right);
    } // if
    if(top > bottom) {
        Swap(top, bottom);
    } // if

    return vec2(left, bottom);
}

vec2 ConputeTexcoordRightBottom(void) {
    float left = uniform_rectangle.x / uniform_size.x;
    float right = uniform_rectangle.z / uniform_size.x;
    float top = uniform_rectangle.y / uniform_size.y;
    float bottom = uniform_rectangle.w / uniform_size.y;

    if(left > right){
        Swap(left, right);
    } // if
    if(top > bottom) {
        Swap(top, bottom);
    } // if

    return vec2(right, bottom);
}

vec2 ConputeTexcoordRightTop(void) {
    float left = uniform_rectangle.x / uniform_size.x;
    float right = uniform_rectangle.z / uniform_size.x;
    float top = uniform_rectangle.y / uniform_size.y;
    float bottom = uniform_rectangle.w / uniform_size.y;

    if(left > right){
        Swap(left, right);
    } // if
    if(top > bottom) {
        Swap(top, bottom);
    } // if

    return vec2(right, top);
}

vec2 ConputeTexcoord(void) {
    switch(gl_VertexID){
    case 0:
        return ConputeTexcoordLeftTop();
    case 1:
        return ConputeTexcoordLeftBottom();
    case 2: 
        return ConputeTexcoordRightBottom();
    case 3:
        return ConputeTexcoordRightTop();
    } // switch
    return vec2(0.0, 0.0);
}

void main() {
    vec4 pos = vec4(vertex_position, 1.0);
    gl_Position = view_projection * model_transform * pos;

    fragment_texcoord = ConputeTexcoord();
}