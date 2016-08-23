#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uv0;
varying vec2 pos0;

uniform mat4 VP;

void main(){

    gl_Position = VP * vec4(position, 1.0);
    uv0 = vec2(uv.x,1 - uv.y);
    pos0 = position.xy;
}
