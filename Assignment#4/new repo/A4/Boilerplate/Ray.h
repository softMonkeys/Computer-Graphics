/*
 * Ray.h
 *
 *  Created on: Nov 8, 2018
 *      Author: heavenel.cerna
 */

#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

class Ray {
public:
	Ray(glm::vec3, glm::vec3);
	virtual ~Ray();

	glm::vec3 evaluate(float);
	glm::vec3 getOrigin() {return origin;}
	glm::vec3 getDirection() {return direction;}

private:
	glm::vec3 origin;
	glm::vec3 direction;
};

#endif /* RAY_H_ */
