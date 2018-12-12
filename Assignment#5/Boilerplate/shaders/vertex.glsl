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
layout(location = 2) in vec3 NormalVec;

uniform mat4 MVP;
uniform mat4 self_rotation;
uniform mat4 orbit_rotation;
// uniform vec3 isSun;

// output to be interpolated between vertices and passed to the fragment stage
out float z;
out vec2 uv;
out vec3 n;
out vec3 l;
out vec3 isSun;

void main()
{
    // assign vertex position without modification
    gl_Position =  MVP * orbit_rotation * self_rotation * vec4(VertexPosition, 1.0);

    vec4 point = orbit_rotation * self_rotation * vec4(VertexPosition, 1.0);

    // assign output colour to be interpolated
	z = VertexPosition[1];
	uv = VertexUV;

  //  vec3 sun = isSun;

    vec4 ns = normalize(orbit_rotation * self_rotation * vec4(NormalVec, 0.0f));
    vec3 n = vec3(ns.x, ns.y, ns.z);

    l = normalize(point).xyz;
}
