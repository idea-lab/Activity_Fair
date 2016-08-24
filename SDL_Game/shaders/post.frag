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

vec2 curve(vec2 uv)
{
	uv = (uv - 0.5) * 2.0;
	uv *= 1.1;	
	uv.x *= 1.0 + pow((abs(uv.y) / 3.2), 2.0);
	uv.y *= 1.0 + pow((abs(uv.x) / 2.4), 2.0);
	uv  = (uv / 2.0) + 0.5;
	uv =  uv *0.92 + 0.04;
	return uv;
}

void main(){

    vec2 uv = curve(uv0);

    vec4 texColor = texture2D(rpColor, uv);
    vec4 blurColor = texture2D(rpBlur, uv);


gl_FragColor =  texColor + blurColor*2;

if (uv.x < 0.0 || uv.x > 1.0)
    gl_FragColor = vec4(0.2);
if (uv.y < 0.0 || uv.y > 1.0)
    gl_FragColor = vec4(0.2);

}