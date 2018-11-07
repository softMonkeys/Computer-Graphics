/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 *      Modified by: BenKun Chen
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <vector>
#include <list>

#include "Geometry.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();



	//Send geometry to the renderer
	void displayScene();

	void changeToSquareScene(int);
	void changeToSpiralScene(int);
	void changeToSierpinskiTriangleScene(float, float, float, float, float, float, int, int);
	void changeToSierpinskiTriangleReloadedScene(int);

	void iterationUp();
	void iterationDown();

	void setIteration(int value){
		iteration = value;
	}

	int iteration = 1;

private:

	std::string sceneType;
	RenderingEngine * renderer;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
