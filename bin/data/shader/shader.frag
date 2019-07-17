#version 120

uniform sampler2DRect tex0;
uniform sampler2DRect noise;

varying vec2 texCoordVarying;
uniform float time;
uniform float mezcla;
uniform vec2  resolution;
uniform float circleMix;
void main()
{
    vec2 st = texCoordVarying.xy;
    vec4 noi = texture2DRect(noise, st*.5);

    float lTime = time*10.0;
    st.x+=sin(lTime+st.y*.02)*20*mezcla;
    vec4 texel0 = texture2DRect(tex0, st);
    vec4 finalMix =mix(texel0,texel0*1.2,noi.r*.3);
    
    float d = distance(st/resolution,vec2(.5));
    d=smoothstep(circleMix,circleMix*.8,d);
    
    
    gl_FragColor = mix(vec4(vec3(1.0)-finalMix.rgb,1.0),finalMix,d);
}
