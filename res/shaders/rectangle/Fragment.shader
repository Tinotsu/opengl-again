#version 330 core
in vec2 TexCoord;
in vec3 vertexColor;
out vec4 FragColor;
uniform sampler2D woodenTexture;

void main()
{
    FragColor = texture(woodenTexture, TexCoord) * vec4(vertexColor, 1.0);
}
