#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 transform;
layout (location = 4) in float useTexture;

out vec3 color;
out vec2 texCoord;
out float useTex;

uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + transform.x + (aPos.x + transform.x) * scale, aPos.y + transform.y + (aPos.y + transform.y) * scale, aPos.z + transform.z + (aPos.z + transform.z) * scale, 1.0);
	color = aColor;
	texCoord = aTex;
	useTex = useTexture;
}