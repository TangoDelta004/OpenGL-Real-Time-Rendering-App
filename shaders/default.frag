#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in float useTex;

uniform sampler2D tex0;

void main()
{
   if (useTex == 1.0f){
      FragColor = texture(tex0, texCoord);
   }
   else{
      FragColor = vec4(color, 0.25f);
   }
}