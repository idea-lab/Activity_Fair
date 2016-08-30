#version 120

uniform sampler2D tex;

varying vec2 uvs[15];

void main(){
    

    vec4 result = vec4(0.0);
    
    /*
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
    */
    
    result += texture2D(tex, uvs[0]) * 0.000007;
    result += texture2D(tex, uvs[1]) * 0.000116;
    result += texture2D(tex, uvs[2]) * 0.001227;
    result += texture2D(tex, uvs[3]) * 0.008465;
    result += texture2D(tex, uvs[4]) * 0.037975;
    result += texture2D(tex, uvs[5]) * 0.110865;
    result += texture2D(tex, uvs[6]) * 0.210786;
    result += texture2D(tex, uvs[7]) * 0.261117;
    result += texture2D(tex, uvs[8]) * 0.210786;
    result += texture2D(tex, uvs[9]) * 0.110865;
    result += texture2D(tex, uvs[10]) * 0.037975;
    result += texture2D(tex, uvs[11]) * 0.008465;
    result += texture2D(tex, uvs[12]) * 0.001227;
    result += texture2D(tex, uvs[13]) * 0.000116;
    result += texture2D(tex, uvs[14]) * 0.000007;
    
    gl_FragColor = vec4(result.xyz, 1.0);
    
    
}