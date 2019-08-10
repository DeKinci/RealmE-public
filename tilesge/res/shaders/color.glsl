#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec4 t1 = texture(texture1, TexCoord);
    FragColor = t1 * t1.a + texture(texture2, TexCoord) * (1.0 - t1.a);
//    FragColor = texture(texture2, TexCoord);
}