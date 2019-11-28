#version 140
//#define GL_compatibility_profile 1
#extension GL_ARB_compatibility: enable

in vec3 vertex;
in vec3 normal;
uniform mat4 matProj;
uniform mat4 matModel;
out vec3 fr_normal;
out vec3 p;


void main()
{
   // Clip Coordinate
   gl_Position = matProj * matModel * vec4(vertex,1);
   //p = vec3(matModel * vertex);
   //fr_normal = vec3(normalize(transpose(inverse(matModel)) * vec4(normal,0)));

}
