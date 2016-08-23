#version 120

uniform sampler2D tex;

varying vec2 uvs[11];

void main(){
    

    vec4 result = vec4(0.0);
	result += texture2D(tex, uvs[0]) * 0.0093;
    result += texture2D(tex, uvs[1]) * 0.028002;
    result += texture2D(tex, uvs[2]) * 0.065984;
    result += texture2D(tex, uvs[3]) * 0.121703;
    result += texture2D(tex, uvs[4]) * 0.175713;
    result += texture2D(tex, uvs[5]) * 0.198596;
    result += texture2D(tex, uvs[6]) * 0.175713;
    result += texture2D(tex, uvs[7]) * 0.121703;
    result += texture2D(tex, uvs[8]) * 0.065984;
    result += texture2D(tex, uvs[9]) * 0.028002;
    result += texture2D(tex, uvs[10]) * 0.0093;
    
    gl_FragColor = vec4(result.xyz, 1.0);
}