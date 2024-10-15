#version 330 core 

in vec3 vertexColor; 

out vec4 FragmentColor; 

void main() 
{
	FragmentColor = vertexColor;
}
