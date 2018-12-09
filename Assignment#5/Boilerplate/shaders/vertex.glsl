// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUV;

uniform mat4 MVP;

// output to be interpolated between vertices and passed to the fragment stage
out vec3 Colour;
out float z;
out vec2 uv;

void main()
{
    // assign vertex position without modification
    gl_Position =  MVP * vec4(VertexPosition, 1.0);

    // assign output colour to be interpolated
	z = VertexPosition[1];
	uv = VertexUV;
}
