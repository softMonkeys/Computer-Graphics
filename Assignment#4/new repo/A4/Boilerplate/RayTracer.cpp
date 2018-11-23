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
			// Calculating the normalized ray for each iteration (i, j)
			float x = (-image.Width() + 1.0f) / 2.0f + i;		// un-normalized x
			float y = (-image.Height() + 1.0f) / 2.0f + j;		// un-normalized y
			float rayLength = sqrt(pow(sqrt(distance * distance + x * x), 2.0f) + pow(y, 2.0f));
			float u = x / rayLength;				// normalized x
			float v = y / rayLength;				// normalized y
			float w = -distance / rayLength;		// normalized z

			Ray ray(glm::vec3(0), glm::vec3(u, v, w));		// ray vector = origin (0, 0, 0) + (x, y, z)
			image.SetPixel(i, j, raycolor(ray, objects, lights));		// detects the colour for each iteration (i, j)
		}
	}
}

/*
 * The method returns:
 * 		true - if the ray hits the nearest object
 * 		false - if the ray hits nothing
 */
bool RayTracer::trace(Ray ray, std::vector<std::unique_ptr<Object>>& objects, Object*& hitObject, glm::vec3& hitPoint, float tMax) {
	float tNear = INFINITY;
	bool hitTrue = false;
	std::vector<std::unique_ptr<Object>>::const_iterator it;	// iterator for all objects
	// Loop through all objects to check if the ray intersects with the object
	for (it = objects.begin(); it != objects.end(); ++it) {
		float t = INFINITY;
		// If the ray intersects with the object, update 't' for nearest object and update the status to true
		if ((*it)->intersect(ray, t) && t < tNear && t < tMax) {
			hitObject = (*it).get();	// get the object that intersects with the ray
			tNear = t;
			hitTrue = true;
			hitPoint = ray.evaluate(t);		// generate the direction vector
		}
	}
	return hitTrue;
}

/*
 * This method returns the color of the pixel for each iteration (i, j) after taking the consideration of shading, shadowing and reflection
 */
glm::vec3 RayTracer::raycolor(Ray ray, std::vector<std::unique_ptr<Object>>& objects, std::vector<Light> lights) {
	glm::vec3 hitColor = glm::vec3(1,1,1) * 0.0f;
	glm::vec3 reflectColor = glm::vec3(0,0,0);
	Object* hitObject;
	glm::vec3 hitPoint;

	// If the ray intersects with the object, calculate the color, otherwise, return black (0, 0, 0)
	if (trace(ray, objects, hitObject, hitPoint, INFINITY)) {
		hitObject->evalNormal(hitPoint);		// get the normal vector for the object
		glm::vec3 ambient = hitObject->getDiffuse() * 0.3f;		// calculate the value for ambient light
		hitColor = ambient;

		glm::vec3 l = glm::normalize(lights[0].getPos() - hitPoint);	// create the ray from the intersection to the light source
		Ray shadowRay(hitPoint + hitObject->getNormal() * 0.00001f, l);		// create an offset (hitObject->getNormal() * 0.00001f) so that the shadow would be intersecting the plane from its origin

		Object* hitObject1;
		glm::vec3 hitPoint1;
		// if the ray intersects an object, it means the origin where the ray shooting from is a shadow, otherwise, it is not a shadow
		if (not trace(shadowRay, objects, hitObject1, hitPoint1, glm::length(l))) {
			glm::vec3 v = glm::normalize(ray.getDirection() - hitPoint);
			glm::vec3 h = glm::normalize((v + l));
			glm::vec3 diffuseComponent = hitObject->getDiffuse() * lights[0].getColour() * std::max(0.0f, glm::dot(hitObject->getNormal(), l));
			glm::vec3 specularComponent = hitObject->getSpec() * lights[0].getColour() * glm::pow(glm::dot(hitObject->getNormal(), h), hitObject->getPhong());
			hitColor = ambient + diffuseComponent + specularComponent;		// the pixel wich is not being considered as shadow needs to have diffuse and specular
		}

		// checks if the given object has reflection property
		// 0 (no reflection) - 1 (full reflection)
		if (hitObject->getReflectance() != 0.0f) {
			glm::vec3 r = glm::normalize(ray.getDirection() - 2.0f * glm::dot(ray.getDirection(), hitObject->getNormal()) * hitObject->getNormal());
			Ray reflectRay(hitPoint + hitObject->getNormal() * 0.00001f, r);
			reflectColor = raycolor(reflectRay, objects, lights);
		}

		hitColor = hitColor * (1 - hitObject->getReflectance()) + reflectColor * hitObject->getReflectance() ;
	}

	return hitColor;
}

void RayTracer::displayScene() {
	image.Render();
}
