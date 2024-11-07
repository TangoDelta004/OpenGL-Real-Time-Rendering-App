#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in float useTexture;
layout (location = 4) in vec3 aNormal;

out vec3 color;
out vec2 texCoord;
out float useTex;
out vec3 Normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 camera;

void main()
{
	fragPos = vec3(model * vec4(aPos,1.0));
	gl_Position = camera * model * vec4(aPos,1.0);
	color = aColor;
	texCoord = aTex;
	useTex = useTexture;
	Normal = aNormal;
}