#version 120

uniform sampler2D tex;
uniform vec3 color;

uniform vec3 glowColor;

varying vec2 uv0;



void main(){
    vec4 texColor = texture2D(tex, uv0);
    gl_FragData[0] = vec4(color, texColor.a);
    gl_FragData[1] = vec4(glowColor,texColor.a);
}