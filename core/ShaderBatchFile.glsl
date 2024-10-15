#version 330 core 
layout (location = 0) in vec3 positionPos; 
layout (location = 1) in vec3 colorsPos; 

out vec3 vertexColor; 

uniform vec4 transformation;

void main() 
{       
	vec4 newPosition = transformation * vec4(positionPos, 1.0);

	gl_Poition = newPosition;

	vertexColor = colorsPos;

}


