/*
* Object.h
*
* Class for storing object
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#ifndef OBJECT_H_
#define OBJECT_H_

#include "imagebuffer.h"
#include "Ray.h"
#include <glm/gtc/matrix_transform.hpp>

class Object {
public:
	Object();
	Object(glm::vec3 col, glm::vec3 norm, glm::vec3 c_r, glm::vec3 c_p, float p);
	virtual ~Object();

	virtual bool intersect(Ray, float&);
	virtual void evalNormal(glm::vec3& p);
	glm::vec3 getColor() { return colour; };
	glm::vec3 getDiffuse() { return diffuseColour; };
	glm::vec3 getSpec() { return specColour; };
	glm::vec3 getNormal() { return normal; };
	float getPhong() { return phong; };

protected:
	glm::vec3 colour;
	glm::vec3 normal;
	glm::vec3 diffuseColour;	//Diffuse coefficient or Surface Color
	glm::vec3 specColour;		//Specular coefficient or Specular color
	float phong;				//Phong exponent, or shininess of material
};

//Sphere Section
class Sphere : public Object {
public:
	Sphere(glm::vec3 c, float r, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p);
	virtual ~Sphere();

	bool intersect(Ray ray, float& t);
	void evalNormal(glm::vec3&);

private:
	glm::vec3 centre;
	float radius;
};

//Triangle Section
class Triangle : public Object {
public:
	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p);
	virtual ~Triangle();

	bool intersect(Ray ray, float& t);
	void evalNormal(glm::vec3&);

private:
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
};

//Plane Section
class Plane : public Object {
public:
	Plane(glm::vec3 n, glm::vec3 poi, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p);
	virtual ~Plane();

	bool intersect(Ray ray, float& t);
	void evalNormal(glm::vec3&) {};

private:
	glm::vec3 point;
};

#endif /* OBJECT_H_ */
