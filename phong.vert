#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

uniform mat4 matProj;
uniform mat4 matModel;
out vec3 normal;
out vec3 p;

void main()
{
   // Clip Coordinate
   gl_Position = matProj * matModel * (gl_Vertex);
   p = vec3(matModel * (gl_Vertex));
   normal = vec3(normalize(transpose(inverse(matModel)) * vec4(gl_Normal,0)));

}
