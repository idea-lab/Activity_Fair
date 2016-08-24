#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uv0;


void main(){

    gl_Position = vec4(position, 1.0);
    uv0 = uv;
    
}