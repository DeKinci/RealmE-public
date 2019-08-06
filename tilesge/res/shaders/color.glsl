//#version 330 core
//in vec3 color;
//out vec4 frag_color;
//void main()
//{
//    frag_color = vec4(color, 1.0);
//}

#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}