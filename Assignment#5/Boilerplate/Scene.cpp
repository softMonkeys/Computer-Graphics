/*
* Scene.cpp
*
*  Created on: Sep 10, 2018
*  Author: John Hall
*/

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "texture.h"



Scene::Scene(RenderingEngine* renderer, GLFWwindow* window) : renderer(renderer), window(window) {
	cmr.theta = 0.0f;
	cmr.phi = 0.0f;
	cmr.r = 15.0f;

	readFile();

	// objects.clear();



//	earth();
//	sun();

//	objects.push_back(sunSphere);
//	objects.push_back(earthSphere);


}

Scene::~Scene() {

}

void Scene::displayScene() {

	renderer->RenderScene(objects, window, cmr);
}

void Scene::sun(){
	InitializeTexture(&sunSphere.texture, "8k_sun.jpg", GL_TEXTURE_2D);



	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	std::cout << out_vertices.size() << std::endl;
	std::cout << out_uvs.size() << std::endl;

	for(int i = 0; i < out_vertices.size(); i++){
		glm::vec3 vertex = out_vertices[i];
		sunSphere.verts.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));

	}

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	sunSphere.drawMode = GL_TRIANGLES;

	for(int i = 0; i < out_uvs.size(); i++){
		glm::vec2 vertex = out_uvs[i];
		sunSphere.uvs.push_back(glm::vec2(vertex.x, vertex.y));
	}

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(sunSphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(sunSphere);

	//Add the triangle to the scene objects
	objects.push_back(sunSphere);

}


void Scene::earth(){
	InitializeTexture(&earthSphere.texture, "8k_earth_daymap.jpg", GL_TEXTURE_2D);


	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	for(int i = 0; i < out_vertices.size(); i++){
		glm::vec3 vertex = out_vertices[i];
		earthSphere.verts.push_back(glm::vec3(vertex.x * 0.5f, vertex.y* 0.5f, vertex.z * 0.5f - 3.0f));

	}

	earthSphere.drawMode = GL_TRIANGLES;

	std::cout << out_vertices.size() << std::endl;
		std::cout << out_uvs.size() << std::endl;

	for(int i = 0; i < out_uvs.size(); i++){
		glm::vec2 vertex = out_uvs[i];
		earthSphere.uvs.push_back(glm::vec2(vertex.x, vertex.y));
	}

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(earthSphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(earthSphere);

	//Add the triangle to the scene objects
	objects.push_back(earthSphere);

}




void Scene::moon(){
	InitializeTexture(&moonSphere.texture, "8k_moon.jpg", GL_TEXTURE_2D);


	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	for(int i = 0; i < out_vertices.size(); i++){
		glm::vec3 vertex = out_vertices[i];
		moonSphere.verts.push_back(glm::vec3(vertex.x * 0.2f, vertex.y* 0.2f, vertex.z * 0.2f - 2.0f));

	}

	moonSphere.drawMode = GL_TRIANGLES;

	std::cout << out_vertices.size() << std::endl;
		std::cout << out_uvs.size() << std::endl;

	for(int i = 0; i < out_uvs.size(); i++){
		glm::vec2 vertex = out_uvs[i];
		moonSphere.uvs.push_back(glm::vec2(vertex.x, vertex.y));
	}

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(moonSphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(moonSphere);

	//Add the triangle to the scene objects
	objects.push_back(moonSphere);

}


void Scene::mars(){
	InitializeTexture(&marsSphere.texture, "8k_mars.jpg", GL_TEXTURE_2D);


	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	for(int i = 0; i < out_vertices.size(); i++){
		glm::vec3 vertex = out_vertices[i];
		marsSphere.verts.push_back(glm::vec3(vertex.x * 0.6f, vertex.y* 0.6f, vertex.z * 0.6f - 4.5f));

	}

	marsSphere.drawMode = GL_TRIANGLES;

	std::cout << out_vertices.size() << std::endl;
		std::cout << out_uvs.size() << std::endl;

	for(int i = 0; i < out_uvs.size(); i++){
		glm::vec2 vertex = out_uvs[i];
		marsSphere.uvs.push_back(glm::vec2(vertex.x, vertex.y));
	}

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(marsSphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(marsSphere);

	//Add the triangle to the scene objects
	objects.push_back(marsSphere);

}



void Scene::milky(){
	InitializeTexture(&milkySphere.texture, "8k_stars_milky_way.jpg", GL_TEXTURE_2D);


	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}

	for(int i = 0; i < out_vertices.size(); i++){
		glm::vec3 vertex = out_vertices[i];
		milkySphere.verts.push_back(glm::vec3(vertex.x * 20.0f, vertex.y* 20.0f, vertex.z * 20.0f));

	}

	milkySphere.drawMode = GL_TRIANGLES;

	std::cout << out_vertices.size() << std::endl;
		std::cout << out_uvs.size() << std::endl;

	for(int i = 0; i < out_uvs.size(); i++){
		glm::vec2 vertex = out_uvs[i];
		milkySphere.uvs.push_back(glm::vec2(vertex.x, vertex.y));
	}

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(milkySphere);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(milkySphere);

	//Add the triangle to the scene objects
	objects.push_back(milkySphere);

}



/*
/ Referenced from: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading
*/
void Scene::readFile(){
	FILE * file = fopen("sphere.obj", "r");
	if(file == NULL){
		printf("Impossible to open the file\n");
		exit(0);
	}
	while(true){
		char lineHeader[128];
		// Read the first word of the line
		int count = fscanf(file, "%s", lineHeader);
		if(count == EOF){
			break;		// if we read till the end of the file, stop reading
		}
		if(strcmp(lineHeader, "v") == 0){
			glm::vec3 vertex;
    	fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    	temp_vertices.push_back(vertex);
		}else if(strcmp(lineHeader, "vt" ) == 0){
			glm::vec2 uv;
    	fscanf(file, "%f %f\n", &uv.x, &uv.y );
    	temp_uvs.push_back(uv);
		}else if(strcmp(lineHeader, "vn") == 0){
			glm::vec3 normal;
    	fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    	temp_normals.push_back(normal);
		}else if(strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
    	unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    	int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    	if(matches != 9){
        	printf("File can't be read\n");
        	exit(0);
    	}
    	vertexIndices.push_back(vertexIndex[0]);
    	vertexIndices.push_back(vertexIndex[1]);
    	vertexIndices.push_back(vertexIndex[2]);
    	uvIndices.push_back(uvIndex[0]);
    	uvIndices.push_back(uvIndex[1]);
    	uvIndices.push_back(uvIndex[2]);
    	normalIndices.push_back(normalIndex[0]);
    	normalIndices.push_back(normalIndex[1]);
    	normalIndices.push_back(normalIndex[2]);
		}
	}



	// For each vertex of each triangle
	for(unsigned int i = 0; i < vertexIndices.size(); i++){
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	// For each UV index of each triangle
	for(unsigned int i = 0; i < uvIndices.size(); i++){
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	// For each normal vector of each triangle
	for(unsigned int i = 0; i < normalIndices.size(); i++){
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		out_normals.push_back(normal);
	}



}
