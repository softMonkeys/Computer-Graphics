/*
* Scene.cpp
*
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#include "Scene.h"
#include "RayTracer.h"
#include "Object.h"
#include "Light.h"

Scene::Scene(RayTracer* raytracer) : raytracer(raytracer) {
	changeToSceneOne();
}


void Scene::changeToSceneOne() {
	objects.clear();
	lights.clear();

	camera = new Camera(55);
	Light light(glm::vec3(0.0f, 2.5f, -7.5f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.9f, -1.925f, -6.69f), 0.825f, glm::vec3(1,0,0), glm::vec3(0.819, 0.843, 0.839), glm::vec3(0), 40, 0.8f)));

	//Pyramid
	float pyramid_reflectance = 0.1;

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.11f, -2.75f, -7.98f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-1.46f, -2.75f, -7.47f), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.0f, 0.0f, 0.1f), 16, pyramid_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.4f, -2.75f, -9.55f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(0.11f, -2.75f, -7.98f), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.0f, 0.0f, 0.0f), 16, pyramid_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-1.46f, -2.75f, -7.47f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-1.97f, -2.75f, -9.04f), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.0f, .0f, .0f), 16, pyramid_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-1.97f, -2.75f, -9.04f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-0.4f, -2.75f, -9.55f), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0.0f, 0.0f, 0.0f), 16, pyramid_reflectance)));

	//Back wall
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -10.5f), glm::vec3(0.231, 0.305, 0.305), glm::vec3(0.819, 0.843, 0.839), glm::vec3(0,0,0), 4, 0)));

	//Green wall on right
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,2.75,-5), glm::vec3(2.75,2.75,-10.5), glm::vec3(2.75,-2.75,-10.5f), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), 2, 0)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,-2.75,-5), glm::vec3(2.75,2.75,-5), glm::vec3(2.75,-2.75,-10.5), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), 2, 0)));

	//Red wall on left
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,-2.75,-5), glm::vec3(-2.75,-2.75,-10.5), glm::vec3(-2.75,2.75,-10.5), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), 2, 0)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,2.75,-5), glm::vec3(-2.75,-2.75,-5), glm::vec3(-2.75,2.75,-10.5), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), 2, 0)));

	//Floor
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), 20, 0.0)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), 20, 0.0)));

	//Ceiling
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,2.75,-10.5), glm::vec3(2.75,2.75,-5), glm::vec3(-2.75,2.75,-5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0,0,0), 20, 0)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,2.75,-10.5), glm::vec3(2.75,2.75,-10.5), glm::vec3(-2.75,2.75,-5), glm::vec3(0.819, 0.878, 0.874), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0,0,0), 20, 0)));

	lights.push_back(light);
}

void Scene::changeToSceneTwo() {
	objects.clear();
	lights.clear();

	camera = new Camera(50);
	Light light(glm::vec3(4.0f, 6.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Floor
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0, 1, 0), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.231, 0.305, 0.305), glm::vec3(0.819, 0.843, 0.839), glm::vec3(0), 100, 0)));

	//Back wall
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -12.0f), glm::vec3(0.372, 0.482, 0.486), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0), 100, 0)));

	//Large yellow sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(1, -0.5, -3.5), 0.5, glm::vec3(0.913, 0.862, 0.247), glm::vec3(0.913, 0.862, 0.247), glm::vec3(0.5, 0.5, 0.5), 120, 0)));

	//Reflective grey sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0, 1, -5), 0.4, glm::vec3(0.349, 0.509, 0.486), glm::vec3(0.349, 0.509, 0.486), glm::vec3(1,1,1), 250, 0.6)));

	//Metallic purple sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(-0.8, -0.75, -4), 0.25f, glm::vec3(0.690, 0.239, 0.819), glm::vec3(0.690, 0.239, 0.819), glm::vec3(1.0f, 1.0f, 1.0f), 180, 0.1)));

	//Green cone
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.4f, -1.0, -5.693f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(0.6928f, -1.0f, -5.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.6928,-1,-5.4), glm::vec3(0,0.6,-5), glm::vec3(0.8,-1,-5), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.8f, -1.0f, -5.0f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(0.6928f, -1.0f, -4.6f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.6928f, -1.0f, -4.6f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(0.4f, -1.0f, -4.307f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.4f, -1.0f, -4.307f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(0.0f, -1.0f, -4.2f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.0f, -1.0f, -4.2f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(-0.4f, -1.0f, -4.307f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.4f, -1.0f, -4.307f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(-0.6928f, -1.0f, -4.6f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.6928f, -1.0f, -4.6f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(-0.8f, -1.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.8f, -1.0f, -5.0f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(-0.6928f, -1.0f, -5.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.6928f, -1.0f, -5.4f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(-0.4f, -1.0f, -5.693f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.4f, -1.0f, -5.693f), glm::vec3(0.0f, 0.6f, -5.0f), glm::vec3(0.0f, -1.0f, -5.8f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.9f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 20, 0)));

	//Shiny,red,icosahedron
	float icosahedron_reflectance = 0.3;

	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2,-1,-7), glm::vec3(
	-1.276,-0.4472,-6.474), glm::vec3(
	-2.276,-0.4472,-6.149), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-1.276,-0.4472,-6.474), glm::vec3(
	-2,-1,-7), glm::vec3(
	-1.276,-0.4472,-7.526), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2,-1,-7), glm::vec3(
	-2.276,-0.4472,-6.149), glm::vec3(
	-2.894,-0.4472,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2,-1,-7), glm::vec3(
	-2.894,-0.4472,-7), glm::vec3(
	-2.276,-0.4472,-7.851), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2,-1,-7), glm::vec3(
	-2.276,-0.4472,-7.851), glm::vec3(
	-1.276,-0.4472,-7.526), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.276,-0.4472,-6.474), glm::vec3(
	-1.276,-0.4472,-7.526), glm::vec3(
	-1.106,0.4472,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.276,-0.4472,-6.149), glm::vec3(
	-1.276,-0.4472,-6.474), glm::vec3(
	-1.724,0.4472,-6.149), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.894,-0.4472,-7), glm::vec3(
	-2.276,-0.4472,-6.149), glm::vec3(
	-2.724,0.4472,-6.474), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.276,-0.4472,-7.851), glm::vec3(
	-2.894,-0.4472,-7), glm::vec3(
	-2.724,0.4472,-7.526), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.276,-0.4472,-7.526), glm::vec3(
	-2.276,-0.4472,-7.851), glm::vec3(
	-1.724,0.4472,-7.851), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.276,-0.4472,-6.474), glm::vec3(
	-1.106,0.4472,-7), glm::vec3(
	-1.724,0.4472,-6.149), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.276,-0.4472,-6.149), glm::vec3(
	-1.724,0.4472,-6.149), glm::vec3(
	-2.724,0.4472,-6.474), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.894,-0.4472,-7), glm::vec3(
	-2.724,0.4472,-6.474), glm::vec3(
	-2.724,0.4472,-7.526), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.276,-0.4472,-7.851), glm::vec3(
	-2.724,0.4472,-7.526), glm::vec3(
	-1.724,0.4472,-7.851), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.276,-0.4472,-7.526), glm::vec3(
	-1.724,0.4472,-7.851), glm::vec3(
	-1.106,0.4472,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.724,0.4472,-6.149), glm::vec3(
	-1.106,0.4472,-7), glm::vec3(
	-2,1,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.724,0.4472,-6.474), glm::vec3(
	-1.724,0.4472,-6.149), glm::vec3(
	-2,1,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-2.724,0.4472,-7.526), glm::vec3(
	-2.724,0.4472,-6.474), glm::vec3(
	-2,1,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.724,0.4472,-7.851), glm::vec3(
	-2.724,0.4472,-7.526), glm::vec3(
	-2,1,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
	-1.106,0.4472,-7), glm::vec3(
	-1.724,0.4472,-7.851), glm::vec3(
	-2,1,-7), glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(1,1,1), 69
	, icosahedron_reflectance)));

	lights.push_back(light);
}

void Scene::changeToSceneThree() {
	objects.clear();
	lights.clear();

	camera = new Camera(50);
	Light light(glm::vec3(4.0f, 6.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Floor
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0, 1, 0), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.231, 0.305, 0.305), glm::vec3(0.819, 0.843, 0.839), glm::vec3(1.0f, 1.0f, 1.0f), 16, 0)));

	//Back wall
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -12.0f), glm::vec3(0.372, 0.482, 0.486), glm::vec3(0.470, 0.796, 0.827), glm::vec3(0), 100, 0)));


	//Ice cream
	glm::vec3 sphere_diffuse = glm::vec3(0.952, 0.803, 0.905);
	glm::vec3 sphere_spec = glm::vec3(0);
	float sphere_phong = 16;
	float sphere_reflectance = 0;
	float sphere_radius = 0.56;

	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0, 1.5, -5), sphere_radius, glm::vec3(0), sphere_diffuse, sphere_spec, sphere_phong, sphere_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.3, 1.3, -5), sphere_radius, glm::vec3(0), sphere_diffuse, sphere_spec, sphere_phong, sphere_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(-0.3, 1.3, -5), sphere_radius, glm::vec3(0), sphere_diffuse, sphere_spec, sphere_phong, sphere_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.0, 1.3, -4.8), sphere_radius, glm::vec3(0), sphere_diffuse, sphere_spec, sphere_phong, sphere_reflectance)));


	//Toppings
	glm::vec3 topping_diffuse = glm::vec3(0.760, 0.058, 0.058);
	glm::vec3 topping_spec = glm::vec3(1,1,1);
	float topping_phong = 40;
	float topping_reflectance = 0.1;
	float topping_radius = 0.1;

	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.62, 1.6, -4.7), topping_radius, glm::vec3(0), topping_diffuse, topping_spec, topping_phong, topping_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(-0.28, 1.85, -4.76), topping_radius, glm::vec3(0), topping_diffuse, topping_spec, topping_phong, topping_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.1, 1.3, -4.31), topping_radius, glm::vec3(0), topping_diffuse, topping_spec, topping_phong, topping_reflectance)));


	//Brown cone
	glm::vec3 cone_diffuse = glm::vec3(0.756f, 0.615f, 0.286f);
	glm::vec3 cone_spec = glm::vec3(0); 
	float cone_phong = 20;
	float cone_reflectance = 0;

	glm::mat3 coneScalingMatrix = glm::scale(glm::mat3(1), glm::vec2(-1.0f, -1.0f));

	glm::mat3 cone_1 = glm::mat3(
		0, -1.0, -5.8,
		0, 0.6, -5,
		0.4, -1.0, -5.693
	);
	glm::mat3 cone_2 = glm::mat3(
		0.4, -1.0, -5.693,
		0, 0.6, -5,
		0.6928, -1.0, -5.4
	);
	glm::mat3 cone_3 = glm::mat3(
		0.6928, -1.0, -5.4,
		0, 0.6, -5,
		0.8, -1.0, -5
	);
	glm::mat3 cone_4 = glm::mat3(
		0.8, -1.0, -5,
		0, 0.6, -5,
		0.6928, -1.0, -4.6
	);
	glm::mat3 cone_5 = glm::mat3(
		0.6928, -1.0, -4.6,
		0, 0.6, -5,
		0.4, -1.0, -4.307
	);
	glm::mat3 cone_6 = glm::mat3(
		0.4, -1.0, -4.307,
		0, 0.6, -5,
		0, -1.0, -4.2
	);
	glm::mat3 cone_7 = glm::mat3(
		0, -1.0, -4.2,
		0, 0.6, -5,
		-0.4, -1.0, -4.307
	);
	glm::mat3 cone_8 = glm::mat3(
		-0.4, -1.0, -4.307,
		0, 0.6, -5,
		-0.6928, -1.0, -4.6
	);
	glm::mat3 cone_9 = glm::mat3(
		-0.6928, -1.0, -4.6,
		0, 0.6, -5,
		-0.8, -1.0, -5
	);
	glm::mat3 cone_10 = glm::mat3(
		-0.8, -1.0, -5,
		0, 0.6, -5,
		-0.6928, -1.0, -5.4
	);
	glm::mat3 cone_11 = glm::mat3(
		-0.6928, -1.0, -5.4,
		0, 0.6, -5,
		-0.4, -1.0, -5.693
	);
	glm::mat3 cone_12 = glm::mat3(
		-0.4, -1.0, -5.693,
		0, 0.6, -5,
		0, -1.0, -5.8
	);

	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_1[0] * coneScalingMatrix, cone_1[1] * coneScalingMatrix, cone_1[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_2[0] * coneScalingMatrix, cone_2[1] * coneScalingMatrix, cone_2[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_3[0] * coneScalingMatrix, cone_3[1] * coneScalingMatrix, cone_3[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_4[0] * coneScalingMatrix, cone_4[1] * coneScalingMatrix, cone_4[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_5[0] * coneScalingMatrix, cone_5[1] * coneScalingMatrix, cone_5[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_6[0] * coneScalingMatrix, cone_6[1] * coneScalingMatrix, cone_6[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_7[0] * coneScalingMatrix, cone_7[1] * coneScalingMatrix, cone_7[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_8[0] * coneScalingMatrix, cone_8[1] * coneScalingMatrix, cone_8[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_9[0] * coneScalingMatrix, cone_9[1] * coneScalingMatrix, cone_9[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_10[0] * coneScalingMatrix, cone_10[1] * coneScalingMatrix, cone_10[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_11[0] * coneScalingMatrix, cone_11[1] * coneScalingMatrix, cone_11[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(cone_12[0] * coneScalingMatrix, cone_12[1] * coneScalingMatrix, cone_12[2] * coneScalingMatrix, glm::vec3(0.0f, 0.0f, 0.0f), cone_diffuse, cone_spec, cone_phong, cone_reflectance)));


	lights.push_back(light);
}

Scene::~Scene() {

}

void Scene::renderScene() {
	raytracer->renderScene(objects, lights, camera);
}










