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

Scene::Scene(RenderingEngine* renderer) : renderer(renderer)
{
	changeToTriangleScene();
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::changeToTriangleScene()
{
	sceneType = "TRIANGLE_SCENE";
	objects.clear();
	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry triangle;
	triangle.verts.push_back(glm::vec3(-0.6f, -0.4f, 1.0f));
	triangle.verts.push_back(glm::vec3(0.0f, 0.6f, 1.0f));
	triangle.verts.push_back(glm::vec3(0.6f, -0.4f, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	triangle.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	triangle.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	triangle.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	triangle.drawMode = GL_TRIANGLES;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(triangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(triangle);

	//Add the triangle to the scene objects
	objects.push_back(triangle);
}

void Scene::changeToCircleScene()
{
	sceneType = "CIRCLE_SCENE";

	objects.clear();

	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry circle;
	int numSegments = 100;
	float du = 2 * 3.14f / numSegments;
	for (float u = 0; u < 2 * 3.14f; u += du)
	{
		//vertex at this value of u
		circle.verts.push_back(glm::vec3(1 * cos(u), 1 * sin(u), 1.0));
		//color at this value of u
		circle.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	circle.drawMode = GL_LINE_STRIP;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(circle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(circle);

	//Add the triangle to the scene objects
	objects.push_back(circle);
}

void Scene::iterationUp()
{
	if (sceneType == "TRIANGLE_SCENE")
	{
		std::cout << "iteration up for triangle scene! Implement me!" << std::endl;
	}
	else if (sceneType == "CIRCLE_SCENE")
	{
		std::cout << "iteration up for circle scene! Implement me!" << std::endl;
	}
}

void Scene::iterationDown()
{
	if (sceneType == "TRIANGLE_SCENE")
	{
		std::cout << "iteration down for triangle scene! Implement me!" << std::endl;
	}
	else if (sceneType == "CIRCLE_SCENE")
	{
		std::cout << "iteration down for circle scene! Implement me!" << std::endl;
	}
}
