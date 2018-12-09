/*
* Scene.h
*	Class for storing objects in a scene
*  Created on: Sep 10, 2018
*      Author: cb-ha
*/

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <iostream>

#include "Geometry.h"
#include "Carmera.h"

using namespace std;

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer, GLFWwindow* window);
	virtual ~Scene();
	Carmera cmr;

	//Send geometry to the renderer
	void displayScene();

	void readFile();
	void earth();
	void sun();
	void moon();
	void mars();
	void milky();

private:
	RenderingEngine * renderer;
	GLFWwindow* window;

	Geometry sunSphere;
	Geometry earthSphere;
	Geometry moonSphere;
	Geometry marsSphere;
	Geometry milkySphere;

	std::vector<Geometry> objects;


	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	std::vector< glm::vec3 > out_vertices;
	std::vector< glm::vec2 > out_uvs;
	std::vector< glm::vec3 > out_normals;


};

#endif /* SCENE_H_ */
