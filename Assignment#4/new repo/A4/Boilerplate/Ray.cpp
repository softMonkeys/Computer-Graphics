/*
 * Ray.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: heavenel.cerna
 */

#include "Ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 d): origin(o), direction(d) {
}

Ray::~Ray() {
}

/*
 * The method returns direction vector for the ray
 */
glm::vec3 Ray::evaluate(float t) {
	return origin + t * direction;
};


