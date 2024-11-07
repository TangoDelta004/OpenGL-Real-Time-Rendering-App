#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in float useTex;
in vec3 Normal;
in vec3 fragPos;

uniform sampler2D tex0;
uniform float opacity;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
   vec3 normalDir = normalize(gl_FrontFacing ? Normal : -Normal);
   float ambient = 0.2f;

   vec3 normal = normalize(Normal);
   vec3 lightDirection = normalize(lightPos-fragPos);

   float diffuse = max(dot(normalDir,lightDirection),0.0f);
   if (useTex == 1.0f){
      FragColor = texture(tex0, texCoord)*lightColor;
   }
   else{
      FragColor = vec4(color, opacity)* lightColor * (diffuse+ambient);
   }
}