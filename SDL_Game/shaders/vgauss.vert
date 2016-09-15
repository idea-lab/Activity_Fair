#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uvs[15];

const float pixelSize = 1.0/240.0;


void main(){

    gl_Position = vec4(position, 1.0);
    for(int i = -7; i < 8; i++){
    
        uvs[i+7] = uv + vec2(0.0, pixelSize*i);
    
    }

}