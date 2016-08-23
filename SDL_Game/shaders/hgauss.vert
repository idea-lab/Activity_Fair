#version 120

attribute vec3 position;
attribute vec2 uv;

varying vec2 uvs[11];

const float pixelSize = 1.0/240.0;


void main(){

    gl_Position = vec4(position, 1.0);
    for(int i = -5; i < 6; i++){
    
        uvs[i+5] = uv + vec2(pixelSize*i, 0.0);
    
    }

}