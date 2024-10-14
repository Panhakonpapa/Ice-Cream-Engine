#version 330 core 
layout (location = 0) in vec3 positionPos; 
layout (location = 1) in vec3 colorsPos; 
layout (location = 2) in vec2 texterCoord;

out vec3 vertexColor; 
out vec2 texterCoordOut;  

uniform vec4 transformation;

void main() 
{       
	vec4 newPosition = transformation * vec4(positionPos, 1.0);

	gl_Poition = newPosition;

	vertexColor = colorsPos;

	texterCoord = texterCoordOut; 
}


