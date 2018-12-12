// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in float z;
in vec2 uv;
in vec3 n;
in vec3 l;
// in vec3 sun;

uniform sampler2D imageTexture;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

void main(void)
{
    //if (sun.x == 0.0f) {
    //    vec4 ca = vec4(0.3, 0.3, 0.3, 0.0);
    //   vec4 cl = vec4(1.0, 1.0, 1.0, 0.0);
    //    // write colour output without modification
    //    vec4 L;

    //    L = ca + cl * max(0, dot(n,l));

    //    FragmentColour =  texture(imageTexture, uv) * L;
    //}
    //else {
        FragmentColour =  texture(imageTexture, uv);
    //}
}
