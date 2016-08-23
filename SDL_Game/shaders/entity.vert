#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uv0;

uniform mat4 vp;
uniform mat4 transform;

void main(){

    gl_Position = vp * transform * vec4(position, 1.0);
    uv0 = vec2(uv.x,1-uv.y);

}