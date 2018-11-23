/*
* RayTracer.h
*
*  Created on: Nov 11, 2018
*      Author: Heavenel Cerna
*/

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "imagebuffer.h"
#include <memory>

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;
class Object;
class Camera;
class Light;
class Ray;

#include <vector>

class RayTracer {
public:
	RayTracer();
	virtual ~RayTracer();

	void renderScene(std::vector<std::unique_ptr<Object>>& objects, std::vector<Light> lights, Camera* camera);
	void displayScene();

	glm::vec3 raycolor(Ray ray, std::vector<std::unique_ptr<Object>>& objects, std::vector<Light> lights);

private:
	bool trace(Ray ray, std::vector<std::unique_ptr<Object>>& objects, Object*& hitObject, glm::vec3& hitPoint, float tMax);
	ImageBuffer image;
};

#endif /* RAYTRACER */
