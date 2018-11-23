/*
* Object.cpp
*
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#include "Object.h"

#include <iostream>
#include <algorithm>

Object::Object(glm::vec3 col, glm::vec3 norm, glm::vec3 c_r, glm::vec3 c_p, float p) {
	colour = col;
	normal = norm;
	diffuseColour = c_r;
	specColour = c_p;
	phong = p;
}

Object::~Object() {
}

bool Object::intersect(Ray ray, float& t)
{
	std::cout << "Object" << std::endl;
	return false;
}

void Object::evalNormal(glm::vec3&)
{
}

//Sphere Section
Sphere::Sphere(glm::vec3 c, float r, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p) : Object(col, glm::vec3(0), c_r, c_p, p) {
	centre = c;
	radius = r;
}

Sphere::~Sphere() {
}

bool Sphere::intersect(Ray ray, float& t) {
	float a = glm::dot(ray.getDirection(), ray.getDirection());
	float b = glm::dot((2.0f * ray.getDirection()), (ray.getOrigin() - centre));
	float c = glm::dot((ray.getOrigin() - centre), (ray.getOrigin() - centre)) - radius * radius;

	float deter = b * b - 4 * a * c;

	float x0, x1;
	if (deter < 0)
		return false;
	else if (deter == 0)
		t = -0.5 * b / a;
	else {
		x0 = (-b + sqrt(deter)) / (2 * a);
		x1 = (-b - sqrt(deter)) / (2 * a);

		if (x0 < 0 && x1 < 0)
			return false;

		t = std::min(abs(x0),abs(x1));
	}

	return true;
}

//bool Sphere::intersect(Ray ray, float& t) {
//	 float t0, t1; // solutions for t if the ray intersects
//
//	// geometric solution
//	glm::vec3 L = centre - ray.getOrigin();
//	float tca = glm::dot(L,ray.getDirection());
//	if (tca < 0) return false;
//	float d2 = glm::dot(L,L) - tca * tca;
//	if (d2 > (radius * radius)) return false;
//	float thc = sqrt((radius * radius) - d2);
//	t0 = tca - thc;
//	t1 = tca + thc;
//
//	if (t0 > t1) std::swap(t0, t1);
//
//	if (t0 < 0) {
//	t0 = t1; // if t0 is negative, let's use t1 instead
//	if (t0 < 0) return false; // both t0 and t1 are negative
//	}
//
//	t = t0;
//
//	return true;
//}

void Sphere::evalNormal(glm::vec3& p) {
	normal = glm::normalize(2.0f * (p - centre));
}

//Triangle Section
Triangle::Triangle(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p) : Object(col, glm::vec3(0), c_r, c_p, p) {
	a = pointA;
	b = pointB;
	c = pointC;
}

Triangle::~Triangle() {
}

bool Triangle::intersect(Ray ray, float& t) {
	glm::mat3 A = glm::mat3(a.x-b.x, a.y-b.y, a.z-b.z,
							a.x-c.x, a.y-c.y, a.z-c.z,
							ray.getDirection().x, ray.getDirection().y, ray.getDirection().z);

	glm::vec3 B = glm::vec3(a.x-ray.getOrigin().x, a.y-ray.getOrigin().y, a.z-ray.getOrigin().z);

	float M = A[0][0]*(A[1][1]*A[2][2] - A[2][1]*A[1][2]) + A[0][1]*(A[2][0]*A[1][2] - A[1][0]*A[2][2]) + A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

	t = -(A[1][2]*(A[0][0]*B.y - B.x*A[0][1]) + A[1][1]*(B.x*A[0][2] - A[0][0]*B.z) + A[1][0]*(A[0][1]*B.z - B.y*A[0][2]))/M;
	if (t < 0)
		return false;

	float v = (A[2][2]*(A[0][0]*B.y - B.x*A[0][1]) + A[2][1]*(B.x*A[0][2] - A[0][0]*B.z) + A[2][0]*(A[0][1]*B.z - B.y*A[0][2]))/M;
	if (v < 0 || v > 1)
		return false;

	float u = (B.x*(A[1][1]*A[2][2] - A[2][1]*A[1][2]) + B.y*(A[2][0]*A[1][2] - A[1][0]*A[2][2]) + B.z*(A[1][0]*A[2][1] - A[1][1]*A[2][0]))/M;
	if (u < 0 || u > 1 - v)
		return false;

	return true;
}

void Triangle::evalNormal(glm::vec3& p) {
	glm::vec3 u = b - a;
	glm::vec3 v = c - a;
	normal = glm::normalize(glm::cross(u, v));
}

//Plane Section
Plane::Plane(glm::vec3 n, glm::vec3 poi, glm::vec3 col, glm::vec3 c_r, glm::vec3 c_p, float p) : Object(col, glm::vec3(0), c_r, c_p, p) {
	normal = n;
	point = poi;
}
Plane::~Plane() {

}

//Referenced from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
bool Plane::intersect(Ray ray, float& t) {
	float check = glm::dot(normal, ray.getDirection());

	if (abs(check) > 0.000001f){
		glm::vec3 v = point - ray.getOrigin();
		t = glm::dot(v, normal) / check;
		return (t >= 0.0f);
	}

	return false;
}

