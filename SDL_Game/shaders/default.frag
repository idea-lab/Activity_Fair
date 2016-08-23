#version 120

uniform sampler2D tex;

varying vec2 uv0;

void main(){
    vec4 texColor = texture2D(tex, uv0);
    gl_FragColor = texColor;
}
