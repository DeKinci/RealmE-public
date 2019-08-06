//#version 330 core
//in vec3 color;
//out vec4 frag_color;
//void main()
//{
//    frag_color = vec4(color, 1.0);
//}

#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){
    color = texture( myTextureSampler, UV ).rgb;
}