#version 120

uniform sampler2D rpColor;
uniform sampler2D rpBlur;
uniform sampler2D rpMotion;

varying vec2 uv0;

const int nSamples = 8;

vec4 blur(sampler2D sampler, vec2 blurVec){

vec4 result = texture2D(sampler, uv0);

for (int i = 1; i < nSamples; ++i) {
   // get offset in range [-0.5, 0.5]:
      //vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);
  
   // sample & add to result:
      result += texture2D(sampler, uv0 + blurVec*i);
}
 
//result /= float(nSamples);

return result;

}

void main(){
    vec4 texColor = texture2D(rpColor, uv0);
    vec4 blurColor = texture2D(rpBlur, uv0);


gl_FragColor =  texColor + blurColor;

//gl_FragColor =  vec4(1.0);
}