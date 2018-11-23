/*
* RayTracer.cpp
*
*  Created on: Nov 11, 2018
*      Author: Heavenel Cerna
*/

#define _USE_MATH_DEFINES

#include "RayTracer.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Ray.h"

#include <iostream>
#include <cmath>
#include <algorithm>

RayTracer::RayTracer() {
	image.Initialize();
}

RayTracer::~RayTracer() {
}

void RayTracer::renderScene(std::vector<std::unique_ptr<Object>>& objects, std::vector<Light> lights, Camera* camera) {
	float distance = (0.5f * image.Width()) / tan((camera->getFov() * M_PI / 180.0f) * 0.5f);

	for (unsigned int i = 0; i < image.Width(); i++) {
		for (unsigned int j = 0; j < image.Height(); j++) {
			float x = (-image.Width() + 1.0f) / 2.0f + i;		// un-normalized x
			float y = (-image.Height() + 1.0f) / 2.0f + j;		// un-normalized y

			float rayLength = sqrt(pow(sqrt(distance * distance + x * x), 2.0f) + pow(y, 2.0f));

			float u = x / rayLength;				// normalized x
			float v = y / rayLength;				// normalized y
			float w = -distance / rayLength;		// normalized z

			Ray ray(glm::vec3(0), glm::vec3(u, v, w));
			image.SetPixel(i, j, raycolor(ray, objects, lights));
		}
	}
}

bool RayTracer::trace(Ray ray, std::vector<std::unique_ptr<Object>>& objects, Object*& hitObject, glm::vec3& hitPoint, float tMax)
{
	float tNear = INFINITY;
	bool hitTrue = false;

	std::vector<std::unique_ptr<Object>>::const_iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		float t = INFINITY;
		if ((*it)->intersect(ray, t) && t < tNear && t < tMax) {
			hitObject = (*it).get();
			tNear = t;
			hitTrue = true;

			hitPoint = ray.evaluate(t);
		}
	}

	return hitTrue;
}

glm::vec3 RayTracer::raycolor(Ray ray, std::vector<std::unique_ptr<Object>>& objects, std::vector<Light> lights)
{
	glm::vec3 hitColor = glm::vec3(0,0,0);
	Object* hitObject;
	glm::vec3 hitPoint;

	if (trace(ray, objects, hitObject, hitPoint, INFINITY)) {
		hitObject->evalNormal(hitPoint);
		glm::vec3 ambient = glm::vec3(1,1,1) * 0.2f;
		hitColor = ambient;
		glm::vec3 l = glm::normalize(lights[0].getPos() - hitPoint);

		Ray shadowRay(hitPoint + hitObject->getNormal() * 0.00001f, l);
		Object* hitObject1;
		glm::vec3 hitPoint1;

		if (not trace(shadowRay, objects, hitObject1, hitPoint1, glm::length(l))) {
			glm::vec3 v = glm::normalize(ray.getDirection() - hitPoint);
			glm::vec3 h = glm::normalize((v + l));
			glm::vec3 diffuseComponent = hitObject->getDiffuse() * lights[0].getColour() * std::max(0.0f, glm::dot(hitObject->getNormal(), l));
			glm::vec3 specularComponent = hitObject->getSpec() * lights[0].getColour() * glm::pow(glm::dot(hitObject->getNormal(), h), hitObject->getPhong());
			hitColor = hitColor + diffuseComponent + specularComponent;
		}
		if (hitColor == ambient && hitObject->getPhong() == 40)
			std::cout << hitObject->getNormal().x << " , " << hitObject->getNormal().y << " , " << hitObject->getNormal().z << std::endl;;
	}

	return hitColor;
}

void RayTracer::displayScene()
{
	image.Render();
}
