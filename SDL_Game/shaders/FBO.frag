#version 120

uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D depthTex;

varying vec2 uv0;
varying vec2 pos0;

void main(){
    //vec4 texColor = vec4(0);
    vec4 color = texture2D(colorTex, uv0);
    vec4 normal = texture2D(normalTex, uv0);
    vec4 depth = texture2D(depthTex, uv0);
    //gl_FragColor = texColor;
    //gl_FragColor = vec4(0);
    gl_FragData[0] = color;
    gl_FragData[1] = normal;
    gl_FragData[2] = vec4(pos0.xy,depth.r/16.0, 1.0);

}
