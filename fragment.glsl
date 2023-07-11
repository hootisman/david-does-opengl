
#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoords;

uniform sampler2D theTexture;
uniform sampler2D theTexture2;

void main()
{
     FragColor = mix(texture(theTexture,texCoords),texture(theTexture2,texCoords),0.6);
};
