#version 330 core 

in vec4 vertexColor; 

out vec4 FragmentColor; 

void main() 
{
	FragmentColor = vertexColor; 
}
