/*
* Light.h
*
* Class for light source
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 c);
	~Light();
	glm::vec3 getPos() { return position; };
	glm::vec3 getColour() { return colour; };

private:
	glm::vec3 position;
	glm::vec3 colour;
};

#endif /* LIGHT_H_ */
