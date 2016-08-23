#version 120

uniform sampler2D colorTex;
uniform sampler2D normalTex;
uniform sampler2D posTex;

uniform float phase;

varying vec2 uv0;

//const vec3 lightPos = vec3(0.19f,0.85f,0.1f);

//const float brightness = 32.0f;

//const vec3 lcolor = vec3(0,1,0);

struct pointLight{

  vec3 pos;
  vec3 col;
  float brightness;
  float phaseOffset; //REMOVE THIS!!! ONLY FOR TESTING
};

const pointLight lights[2] = pointLight[2](pointLight( vec3(0.15f,0.85f,0.1f), vec3(0.5,1,0.5), 32.0f, 0.0f),
                                           pointLight( vec3(0.15f,0.85f,0.1f), vec3(1,0.5,0.5), 32.0f, 3.14f));

const vec3 ambient = vec3(0.1,0.1,0.1);

void main(){

    vec4 color = texture2D(colorTex, uv0);
    vec3 normal = 2 * (texture2D(normalTex, uv0).xyz - .5);
    vec3 worldPos = texture2D(posTex, uv0).xyz;

    vec3 sum = ambient*color.xyz;


    for(int i = 0; i <2; i++){

    float distance = length(vec3(lights[i].pos.x+sin(phase+lights[i].phaseOffset)/16.0,lights[i].pos.y+cos(phase+lights[i].phaseOffset)/16.0,lights[i].pos.z)-worldPos) * 64;

      if(distance < 7.5){
        float attenuation = 1.0f/(distance*distance*distance);
        vec3 lightDirection = normalize(vec3(lights[i].pos.x+sin(phase+lights[i].phaseOffset)/16.0,lights[i].pos.y+cos(phase+lights[i].phaseOffset)/16.0,lights[i].pos.z)-worldPos);
        sum += lights[i].col * lights[i].brightness * attenuation * color.xyz * clamp(dot(normal.xyz, lightDirection),0.0, 1.0);
      }else if(distance < 7.7){
        sum = vec3(1.0,1.0,0.0);
      }

    }
    gl_FragColor = vec4(sum, color.a);
    //gl_FragColor = vec4(worldPos,1.0);
}
