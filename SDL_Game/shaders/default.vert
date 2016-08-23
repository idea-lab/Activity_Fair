#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uv0;

uniform mat4 VP;

void main(){

    gl_Position = VP * vec4(position, 1.0);
    uv0 = uv;

}
