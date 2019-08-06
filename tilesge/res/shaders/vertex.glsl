//#version 330 core
//uniform mat4 MVP;
//in vec3 vCol;
//in vec2 vPos;
//out vec3 color;
//void main()
//{
//    gl_Position = MVP * vec4(vPos, 0.0, 1.0);
//    color = vCol;
//}

#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}
