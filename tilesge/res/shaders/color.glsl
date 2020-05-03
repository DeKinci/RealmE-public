#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture;

void main()
{
    vec4 texColor = texture(texture, TexCoord);
    if (texColor.a < 0.01) {
        discard;
    }
    FragColor = texColor;
}