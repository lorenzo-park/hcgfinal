#version 140
#extension GL_ARB_compatibility: enable
in vec3 p;
in vec3 normal;
uniform float k_a, k_d, k_s, alpha;
uniform vec3 diffuse, ambient, specular, lightPos;

void main()
{

   vec3 v = normalize(vec3(0, 0, 1)-p); //The default camera is at distance 1.0 of the center point [0.,0.,0.] and looking in the -z direction.
    vec3 n = normalize(normal);
   vec3 l = normalize(lightPos-p);
   vec3 r = normalize(reflect(l, n));
   vec3 amb = k_a * ambient;
   vec3 diff = k_d * max(dot(l,n),0) * diffuse;
   vec3 spec = k_s * pow(max(dot(r,v),0), alpha) * specular;
   float dist = length(vec3(lightPos-p));

   gl_FragColor = vec4(amb+diff+spec,1);
//   if(diffuse.x == 1) gl_FragColor = vec4(1, 0, 0, 1);
//   else gl_FragColor = vec4(0,1,0,1);


}
