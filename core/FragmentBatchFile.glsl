#version 330 core 

in vec3 vertexColor; 
in vec2 texterCoord; 

out vec4 FragmentColor; 

uniform sample2D ourtexture;

void main() 
{
	FragmentColor =  texture(ourTexture, TexCoord);
}
