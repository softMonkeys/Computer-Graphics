/*
* Light.cpp
*
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#include "Light.h"

#include <glm/glm.hpp>

Light::Light(glm::vec3 pos, glm::vec3 c) {
	position = pos;
	colour = c;
}

Light::~Light()
{
}
