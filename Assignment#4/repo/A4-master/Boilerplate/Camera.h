/*
* Camera.h
*
* Class for representing Camera
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(float angle);
	virtual ~Camera();

	float getFov() {return fov;}
	void setFov(float f) { fov = f; }

private:
	float fov;
};

#endif /* CAMERA_H_ */
