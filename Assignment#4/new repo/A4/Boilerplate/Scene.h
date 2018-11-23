/*
* Scene.h
*  
* Class for storing objects in a scene
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#ifndef SCENE_H_
#define SCENE_H_

#include "Camera.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <vector>
#include <memory>

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RayTracer;
class Object;
class Light;

class Scene {
public:
	Scene(RayTracer* raytracer);
	virtual ~Scene();

	void changeToSceneOne();
	void changeToSceneTwo();
	void changeToSceneThree();

	void renderScene();
	Camera* getCamera() { return camera; };

private:
	RayTracer* raytracer;

	//list of objects in the scene
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<Light> lights;
	Camera* camera;
};

#endif /* SCENE_H_ */
